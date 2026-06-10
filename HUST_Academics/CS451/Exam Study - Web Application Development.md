# Exam Study — Web Application Development

**Source PPTX:** WebApplicationDevelopment_1.pptx — CS451 Supplementary Slides (39 slides)  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #CS451 #exam #web-dev #PHP #nginx #MySQL #HTTP #sessions #cookies

---

## Executive Summary

This module builds the web development foundation required to understand every web application attack. A web application is **two programs running at two separate locations** — a frontend (browser) and a backend (server) — connected by HTTP request-reply cycles. The key insight is that **the browser is untrusted territory**: any data the server receives from the browser must be treated as potentially hostile, which is why parameterized queries, CSRF tokens, output sanitization, and session regeneration are mandatory. Understanding exactly how PHP sessions, cookies, MySQL queries, and nginx routing work is what makes each attack in the companion Web Application Security module make sense.

---

## 1. Application Classifications

Applications differ along three dimensions: **Purpose**, **Users**, and **Runtime Environment**. The runtime environment is the most important for security.

| Runtime Category | Examples | Where Code Runs |
|---|---|---|
| **Native Applications** | Desktop apps, Mobile apps | On the user's device (OS-native) |
| **Scripting Applications** | Shell scripts, Python scripts | On a host machine |
| **Web Applications** | SocialNet, Gmail, Facebook | **Split**: frontend in browser, backend in server |

> **Web applications are the most important type today** — they dominate commercial software and are the primary attack surface in network security.

---

## 2. Web Application Overview

### The Client–Server Model

```
┌──────────────────────┐         HTTP          ┌──────────────────────┐
│        CLIENT        │ ◄──────────────────── │        SERVER        │
│  (Browser / GUI)     │ ──────────────────── ► │  (Logic + Data)      │
└──────────────────────┘    Request / Reply     └──────────────────────┘
```

- **Client** (browser): provides the interactive, user-facing graphical interface.
- **Server**: provides business logic according to user interactions; stores user data (centralized data management).

### Why Web Applications Are Important

| Perspective | Benefit |
|---|---|
| **End User** | No software installation required — just a browser; nice GUI widgets; very lightweight client |
| **Service Provider** | Centralized deployment: deploy once, serve many; centralized data management |
| **Developer** | Highly customizable, flexible, reusable technology stacks; quick to develop |

---

## 3. Technology Stack

### The Fundamental Split

```
Web Application
├── Frontend (runs INSIDE the browser)
│   ├── HTML         — content structure
│   ├── CSS          — content styling
│   └── JavaScript   — client-side logic (animation, request sending, data visualization, user input)
│       └── DOM API  — set of browser functions for programmatic page manipulation
│
└── Backend (runs INSIDE the server)
    ├── Application Server (PHP / Java / NodeJS / Python / ...)
    ├── Database Server   (MySQL / MongoDB / ...)
    └── Supplementary     (Redis, Memcache, ...)
```

> **Critical for security**: PHP executes on the **server** at request time. JavaScript executes in the **browser** after page load. Never confuse where code runs.

### Frontend Technologies

- **ONE single standardized stack** — no alternative exists: HTML + CSS + JavaScript.
- Runs entirely within the **browser's runtime environment**.
- **DOM API** (Document Object Model): the set of browser functions that JavaScript uses to programmatically interact with and modify page content.

**Skill levels:**
| Level | Technologies |
|---|---|
| Minimalist | HTML + CSS + JavaScript + DOM API |
| Intermediate/Advanced | + React / Angular / Vue / ... |

### Backend Technologies

- **MANY options** — choose a stack and master it:
  - Application server: PHP, Java, NodeJS, Python, ...
  - Database server: MySQL (RDBMS), MongoDB (NoSQL), ...
  - Supplementary: Redis (cache), Memcache, ...
- **Easy to scale** with load balancers: HAProxy, nginx, Apache.
- Application servers are **optional** for static sites but **expected** as soon as dynamic features are needed.

**Backend skill choices:**
| Tier | Technologies |
|---|---|
| Application server | PHP, Java, Python, NodeJS |
| Database | SQL (MySQL), NoSQL (MongoDB), Cache (Redis) |
| Infrastructure | Load balancing, Git, server administration |

---

## 4. Frontend–Backend Interaction

### HTTP Request–Reply Cycle

All frontend–backend communication occurs **over HTTP**:
- Each Request–Reply cycle corresponds to exactly **one URL**.
- Each Request–Reply cycle returns exactly **one page or web object**.

**Example flow:**
```
1. Client sends Request (for a URL)
2. Backend produces output for that URL
3. Backend sends output in a Reply
4. Client receives Reply → renders a page (or manipulates current page via AJAX)
```

### Backend Request Processing

The backend has **no "main" function**. It is structured as a collection of **request handlers** — one function per URL pattern:

```
Request arrives (e.g., URL: /profile.php?owner=alice)
    ↓
Request handler for /profile.php
    ├── Parse request parameters (query string, POST body, headers, cookies)
    ├── Query DB: SELECT * FROM account WHERE username='alice'
    └── Format queried data → build HTML response → send Reply
```

**Typical backend handler tasks:**
1. **Parse request** — extract parameters from query string, headers, form body, cookies.
2. **Query DB** — fetch or modify data.
3. **Format** — build an appropriate response (HTML page, JSON, redirect).

### Frontend Processing

Browser-side JavaScript:
1. **Actively sends requests**: user types URL in address bar, or JavaScript code sends requests on user actions.
2. **Waits for reply**.
3. **Processes the reply**: either renders a full new page, or manipulates current page (**AJAX** — Asynchronous JavaScript and XML).

### Ways to Send Requests from the Browser

| Mechanism | Used For |
|---|---|
| Address bar navigation | User explicitly types URL |
| HTML `<form>` element | Form submissions (login, registration, settings) |
| HTML `<img>`, `<script>` src attributes | Resources loaded automatically — **also exploited in CSRF** |
| JavaScript `fetch()` function | AJAX requests (dynamic updates without full page reload) |

---

## 5. PHP Request Handling

### Request Methods

| Method | Purpose | PHP Access |
|---|---|---|
| `GET` | Retrieve data; parameters in URL query string | `$_GET['param']` |
| `POST` | Upload data; parameters in request body | `$_POST['param']` |

Detect request method: `$_SERVER['REQUEST_METHOD']`

### PHP Superglobals Reference

| Superglobal | Contains |
|---|---|
| `$_GET` | URL query string parameters |
| `$_POST` | Form POST body parameters |
| `$_COOKIE` | All cookies sent by the browser |
| `$_SESSION` | Server-side session data for current PHPSESSID |
| `$_SERVER` | Request metadata (method, headers, server info) |

### PHP Template — Dynamic vs Static

PHP code is embedded in HTML using `<?php ... ?>` tags. The **server executes PHP at request time**; the browser receives only the resulting HTML.

```php
<!-- Static content (sent as-is): -->
<h1>Welcome</h1>

<!-- Dynamic content (executed on server, result sent to browser): -->
<?php echo "Hello, " . $_SESSION['username']; ?>

<!-- JavaScript: runs in the browser AFTER the server sends the page -->
<script>alert("This runs in browser");</script>
```

### Page Navigation — PHP Redirection

```php
header("Location: /target-page.php");
exit();   // MUST call exit() to stop further PHP execution after redirect
```

### PHP File Content Reuse

```php
require 'config.php';        // fatal error if file not found
require_once 'config.php';   // include only once (prevents re-inclusion bugs)
include 'header.php';        // warning if not found (non-fatal)
include_once 'header.php';   // include only once
```

### Debugging

```php
phpinfo();   // displays all PHP configuration and environment variables
```

Configure error reporting level in `php.ini` (verbose for development, minimal for production).

---

## 6. Cookies and Sessions — The Authentication Mechanism

> **Security-critical section**: cookies and sessions are the exact mechanism exploited in ATT-6 and ATT-7.

### How Cookies Work

```
Server Response:  Set-Cookie: PHPSESSID=abc123; HttpOnly; Secure; SameSite=Strict
Browser Storage:  keyed by domain name (and port)
Browser Action:   automatically includes Cookie: PHPSESSID=abc123 in EVERY subsequent request
```

The cookie mechanism is **automatic and invisible** to the user. This is:
- What enables session persistence.
- What makes session hijacking possible when cookies are unprotected.

**PHP cookie functions:**
```php
setcookie('name', 'value', $expiry, '/', '', true, true);  // set a cookie
$_COOKIE['name'];   // read a cookie
header("Set-Cookie: name=value; HttpOnly; Secure");  // manual header
```

### Sessions in PHP

A **session** is a server-side storage space for one browser's interactions.

| Property | Value |
|---|---|
| Session key | `PHPSESSID` (session ID) |
| Storage location | Server-side (default: `/tmp` files, or database) |
| Transmission to browser | As a cookie (`Set-Cookie: PHPSESSID=...`) |
| Browser's role | Automatically sends `PHPSESSID` in every request |

**Session lifecycle:**

```php
session_start();                    // 1. creates or resumes a session
session_id();                       // 2. returns the current PHPSESSID
$_SESSION['key'] = 'value';         // 3. read/write session data
session_regenerate_id(true);        // 4. CRITICAL on login (defeats session fixation)
session_destroy();                  // 5. invalidates the session (on logout)
```

**Login flow — correct implementation:**
```php
session_start();
if (login_successful($username, $password)) {
    session_regenerate_id(true);           // defeat session fixation!
    $_SESSION['username'] = $username;    // store authenticated state
    header("Location: home.php");
    exit();
}
```

**Session check on every protected page:**
```php
session_start();
if (!isset($_SESSION['username'])) {
    header("Location: signin.php");   // redirect unauthenticated users
    exit();
}
// serve protected content to $_SESSION['username']
```

---

## 7. Password Security in PHP

**Never** store passwords in plaintext. PHP provides built-in bcrypt functions:

```php
// Account creation: hash the plaintext password
$hash = password_hash($plaintext_password, PASSWORD_DEFAULT);
// Result: 60-character bcrypt hash → store this in DB

// Login verification: compare plaintext against stored hash
$is_valid = password_verify($plaintext_password, $stored_hash);
// Returns: TRUE or FALSE
```

**Why bcrypt:**
- Computationally expensive by design — brute-force attacks are slow.
- Each hash includes a **unique random salt** — two identical passwords produce different hashes.
- `PASSWORD_DEFAULT` automatically upgrades to the strongest available algorithm as PHP versions evolve.

---

## 8. MySQL with PHP

### Setup Flow (Ubuntu)

```bash
sudo apt-get install mysql-server

mysql -u root -p

CREATE DATABASE socialnet;
CREATE USER 'webapp'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON socialnet.* TO 'webapp'@'localhost';
FLUSH PRIVILEGES;
```

- **Adminer**: lightweight web-based database management GUI (alternative to phpMyAdmin).
- Reconfigure MySQL to listen on a **network socket** for PHP-FPM to connect over TCP.

### SocialNet Database Schema

```sql
-- User accounts
CREATE TABLE account (
    id       INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    password VARCHAR(60) NOT NULL,   -- bcrypt hash, always 60 chars
    fullname VARCHAR(100),
    gender   VARCHAR(10)
);

-- Friend relationships (bidirectional pairs)
CREATE TABLE friend (
    account_id INT,
    friend_id  INT,
    PRIMARY KEY (account_id, friend_id)
);
```

### Working with SELECT Queries (Parameterized — Secure)

```php
// Pattern: Open connection → Execute query → Fetch results
$pdo = new PDO("mysql:host=localhost;dbname=socialnet", $user, $pass);

// Parameterized query — safe against SQL injection
$stmt = $pdo->prepare("SELECT * FROM account WHERE username = ?");
$stmt->execute([$username]);
$row  = $stmt->fetch(PDO::FETCH_ASSOC);     // single row
$rows = $stmt->fetchAll(PDO::FETCH_ASSOC);  // all rows (use in a loop)
```

> **Why parameterized queries are mandatory**: the DB driver compiles the query structure BEFORE user input is provided. Input is treated purely as data — SQL metacharacters (`'`, `--`, `UNION`) inside it are **never interpreted as SQL syntax**. This defeats all three SQL injection variants (ATT-3, ATT-4, ATT-5).

---

## 9. Server Environment: nginx + PHP-FPM

### Web Server vs Application Server

| Component | Role |
|---|---|
| **nginx** | Receives HTTP requests; serves static files; proxies dynamic `.php` requests to PHP-FPM |
| **PHP-FPM** | PHP FastCGI Process Manager; executes PHP scripts; returns output to nginx |

### Key nginx Commands

```bash
sudo apt-get install nginx             # install
sudo systemctl start nginx             # start
sudo systemctl stop nginx              # stop
sudo systemctl status nginx            # check status
sudo ss -tlnp | grep nginx             # check listening ports

# Configuration files:
/etc/nginx/nginx.conf
/etc/nginx/sites-available/default     # default virtual server config
```

**nginx concepts:**
- **Document root**: directory where nginx serves static files from (default: `/var/www/html/`).
- File ownership must match nginx's user account (typically `www-data`).
- **Virtual servers**: nginx can serve multiple domains/ports from one instance.

**nginx integration with PHP-FPM (config snippet):**
```nginx
location ~ \.php$ {
    fastcgi_pass unix:/run/php/php8.1-fpm.sock;
    include fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
}
```

### Key PHP-FPM Commands

```bash
sudo apt-get install php-fpm           # install
sudo systemctl start php8.1-fpm       # start
sudo systemctl status php8.1-fpm      # check status
ps aux | grep php-fpm                  # show processes
sudo ss -tlnp | grep php               # check listening socket
```

---

## 10. Key Skill: Control Your Environments

Mastering environments is a core practical skill:

| Environment | What to Master |
|---|---|
| **Browser** | Developer Tools: Console / Network / Elements / Application (cookies, storage) |
| **Application Server** | How to install (apt-get); configure (config files); run (systemctl) |
| **DB Server** | MySQL CLI commands; creating databases/users; granting privileges |
| **Web Server** | nginx config; document root; virtual servers; PHP-FPM integration |
| **Version Control** | Git-based collaboration; GitHub/GitLab workflows |

---

## 11. SocialNet Application

### Features

- Account Registration
- Login / Logout
- Make Friend
- View profile page (**friends only** — this access control is the source of ATT-1)

### Page Transition Diagram

```
               [not signed in]
                     │
         ┌─────► signin.php ◄──────────────────┐
         │           │                          │
Wrong    │    Login  │ successfully             │ Click "Logout"
creds    │           ▼                          │ (session_destroy)
         └────── home.php ───────────────► signout.php
                     │
                     ├── make friend (stranger → friend relationship)
                     │
                     └──► setting.php (edit profile)
                               │
                          profile.php (friend's profile — auth required)
```

### Implementation Sequence

| Step | Page | Key Implementation |
|---|---|---|
| 1 | Admin form | Create initial user accounts (admin-only) |
| 2 | signin.php | Login form (POST) → `password_verify()` → store username in `$_SESSION` |
| 3 | home.php | Check `$_SESSION['username']`; if absent → redirect to `signin.php` |
| 4 | signout.php | `session_destroy()` → redirect to `signin.php` |
| 5 | setting.php | Edit profile (protected; requires session check) |
| 6 | profile.php | View friend's profile (**access control: must check friend relationship**) |

---

## 12. Lab Exercises Reference

| Lab | Topic | Key Skills |
|---|---|---|
| **Lab 1: Static Webserver** | nginx control | install, start/stop, check processes/ports, config files, virtual servers, document root, file ownership |
| **Lab 2: Static Web on nginx** | Serve HTML | edit HTML, copy to document root, set ownership/mode, verify in browser, add image |
| **Lab 3: JavaScript** | Frontend scripting | W3Schools JS tutorial; DOM manipulation |
| **Lab 4: PHP-FPM** | Application server | install php-fpm, integrate with nginx, test with `phpinfo()`, hello-world PHP |

---

## Deep Dive: The Security Architecture of Client–Server

The **frontend/backend split** creates fundamental security complexity:

**The client is untrusted territory.** The browser is a device the attacker controls. Any data sent from the browser (forms, query strings, cookies, headers) must be treated as **potentially hostile**. The backend can never assume:
- The data comes from the application's own legitimate form.
- The data has not been modified between browser and server.
- The user sending the request is who they claim to be (session cookie present ≠ request was intentional — see CSRF/ATT-1).

**Defense principle**: "Verify everything on the server; trust nothing from the client."

This explains why:
- **Parameterized queries** → defeats SQL injection (ATT-3, ATT-4, ATT-5)
- **CSRF tokens** → defeats unauthorized URL navigation (ATT-1, ATT-2)
- **Output sanitization** → defeats stored XSS (ATT-6, ATT-7)
- **`session_regenerate_id()`** → defeats session fixation (ATT-7)
- **`HttpOnly` cookie flag** → defeats cookie theft via JavaScript (ATT-6)

None of these are optional hardening — they are **mandatory compensations** for the fundamental untrustworthiness of client-supplied data.

---

## Key Takeaways for the Exam

1. **A web application = 2 programs** — frontend (browser, JS/HTML/CSS) and backend (server, PHP+DB) — connected via HTTP request-reply.
2. **PHP runs on the server at request time**; JavaScript runs in the browser after page load. Never mix these up.
3. **Superglobals**: `$_GET`, `$_POST`, `$_COOKIE`, `$_SESSION`, `$_SERVER`.
4. **Sessions use cookies** (`PHPSESSID`) to link browser state to server-side data — this is the mechanism exploited in ATT-6 and ATT-7.
5. **`session_regenerate_id(true)` on login** is mandatory — without it, session fixation (ATT-7) is trivial.
6. **`password_hash()` and `password_verify()`** are PHP's bcrypt functions — always use them; never store plaintext passwords.
7. **Parameterized queries** (`PDO::prepare()`) eliminate all SQL injection variants with a single architectural choice.
8. **nginx** serves HTTP; **PHP-FPM** executes PHP; they communicate via FastCGI socket.
9. **The browser is untrusted** — all validation, authorization, and sanitization must happen on the server.
10. **Ways to send HTTP requests from browser**: address bar, HTML form, `<img>`/`<script>` src, JavaScript `fetch()`.

---

## Knowledge Check Q&A

**Q1**: What is the difference between `$_GET` and `$_POST`?  
**A**: `$_GET` contains parameters from the URL query string (visible in address bar). `$_POST` contains parameters from the HTTP request body (form submissions). `$_GET` is used for retrieving data; `$_POST` for uploading/submitting data.

**Q2**: Why must `session_regenerate_id(true)` be called on successful login?  
**A**: Without it, a session ID set before login remains valid after authentication — enabling session fixation (ATT-7). Regenerating the session ID on login invalidates any pre-set session ID, so an attacker who fixed the session ID cannot use it.

**Q3**: What is the difference between a static and dynamic web page in PHP?  
**A**: Static content is sent as-is (plain HTML). Dynamic content is PHP code executed on the server at request time — the browser receives only the resulting HTML, not the PHP code.

**Q4**: Why are parameterized queries more secure than string concatenation for SQL?  
**A**: The DB driver compiles the query structure before user input is provided. Input is treated as data — SQL metacharacters inside it are never interpreted as SQL syntax. String concatenation lets user input become part of the SQL structure, enabling injection attacks.

**Q5**: What is the role of nginx vs PHP-FPM?  
**A**: nginx is the web server — it receives HTTP requests, serves static files, and proxies `.php` requests to PHP-FPM. PHP-FPM is the application server — it executes PHP scripts and returns the output to nginx via FastCGI.

**Q6**: Why is profile.php a security risk in SocialNet if access control is not implemented?  
**A**: If profile.php only checks "is the user logged in?" rather than "is the session user a friend of the profile owner?", any authenticated user can view any profile by directly navigating to `profile.php?owner=userX` — this is ATT-1 (unauthorized profile access).

---

## Graph View Links

**Previous**: [[Module 8 - Network Security]]  
**Next**: [[Supplementary - Web Application Security]]  
**Hub**: [[CS451 - Hub]]  
**Source Notes**: [[Supplementary - Web Application Development]]
