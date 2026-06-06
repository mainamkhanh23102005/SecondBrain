# Supplementary – Web Application Development

**Source:** CS451 Lecture Slides — Supplementary: Web Application Development / Information Security  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #web-dev #PHP #nginx #MySQL #HTTP #sessions #cookies #CS451

---

## Executive Summary

This supplementary module provides the web development foundation needed to understand and attack web applications in [[Supplementary - Web Application Security]]. It covers the complete technology stack of a web application — from the conceptual client-server split, through the concrete technologies (nginx, PHP-FPM, MySQL), to the HTTP-level mechanics of requests, cookies, and sessions. The capstone project is **SocialNet**, a minimal PHP social network whose features (registration, login, friend management, profile viewing) map directly to the security attack scenarios in the companion module.

> **Why This Matters for Security**: You cannot effectively attack or defend what you do not understand. Every SQL injection, session hijack, and CSRF exploit depends on knowing exactly how the backend processes requests, how sessions are stored, and how cookies flow between browser and server.

---

## 1. Application Classifications

Applications differ along three dimensions:
- **Purpose**: what task they perform
- **Users**: who interacts with them
- **Runtime Environment** ← the critical dimension for security

| Runtime Category | Examples | Where Code Runs |
|---|---|---|
| **Native Applications** | Desktop apps, Mobile apps | On the user's device (OS-native) |
| **Scripting Applications** | Shell scripts, Python scripts | On a host machine directly |
| **Web Applications** | SocialNet, Gmail, Facebook | **Split**: frontend in browser, backend in server |

**Web applications are the most important category today** because they dominate commercial software and are the primary attack surface for network security.

---

## 2. Web Application Architecture

### The Client-Server Model

```
┌──────────────────────┐         HTTP          ┌──────────────────────┐
│        CLIENT        │ ◄──────────────────── │        SERVER        │
│  (Browser / GUI)     │ ──────────────────── ► │  (Logic + Data)      │
└──────────────────────┘    Request / Reply     └──────────────────────┘
```

- **Client** (browser): provides the interactive, user-facing graphical interface.
- **Server**: provides business logic according to user interactions; stores user data centrally (centralized data management).

### Why Web Applications Dominate

| Perspective | Benefit |
|---|---|
| **End User** | No software installation required; just a browser. Nice GUI widgets. Very lightweight client. |
| **Service Provider** | Centralized deployment: deploy once, serve many users. Centralized data management. |
| **Developer** | Highly customizable, flexible, reusable technology stacks; quick to develop. |

---

## 3. Technology Stack

A web application is **two programs running at two separate locations**:

```
Web Application
├── Frontend (runs INSIDE the browser)
│   ├── HTML         — content structure
│   ├── CSS          — content styling
│   └── JavaScript   — client-side logic (animation, request sending, data visualization, user input)
│       └── DOM API  — set of browser functions for programmatic page manipulation
│
└── Backend (runs INSIDE the server)
    ├── Application Server (Java / PHP / NodeJS / Python / ...)
    ├── Database Server   (RDBMS / noSQL)
    └── Supplementary     (Redis, Memcache, ...)
```

### Frontend Technologies

- **ONE standardized stack** — there is no alternative: HTML + CSS + JavaScript.
- Runs entirely within the **browser's runtime environment**.
- The **DOM API** (Document Object Model) provides functions to interact with the browser and modify page content programmatically.

**Skill levels:**
- **Minimalist**: HTML + CSS + JavaScript + DOM API
- **Intermediate to Advanced**: + React / Angular / Vue / ...

### Backend Technologies

- **MANY options** — pick a stack and master it:
  - Application server: PHP, Java, NodeJS, Python, ...
  - Database server: MySQL (RDBMS), MongoDB (noSQL), ...
  - Supplementary: Redis (cache), Memcache, ...
- **Easy to scale**: load balancers (Haproxy, nginx/apache) distribute requests across multiple application server instances.
- Application servers are optional in static sites but **expected** as soon as the application needs dynamic features.

---

## 4. Frontend–Backend Interaction

### HTTP Request-Reply Cycle

- All communication between frontend and backend occurs **over HTTP**.
- Interaction is structured as **Request-Reply cycles**:
  - Each Request–Reply pair corresponds to exactly **one URL**.
  - Each Request–Reply pair returns exactly **one page or web object**.

**Example flow:**
```
1. Client sends a Request (for a URL)
2. Backend produces output for that URL
3. Backend sends the output in a Reply
4. Client receives Reply → renders a page (or manipulates current page via AJAX)
```

### Backend Request Processing

The backend has no "main" function. It is structured as a collection of **request handlers** — one function per URL pattern:

```
Request arrives (URL: /profile?user=alice)
    ↓
Request handler for /profile
    ├── Parse request parameters (query string, POST body, headers, cookies)
    ├── Query DB: SELECT * FROM accounts WHERE username='alice'
    └── Format queried data → build HTML response → send Reply
```

Typical backend handler tasks:
1. **Parse request** to extract parameters (query string, headers, form body, cookies).
2. **Query DB** to fetch or modify data.
3. **Format** the queried data into an appropriate response (HTML page, JSON, redirect).

### Frontend Processing

The browser-side JavaScript:
1. **Actively sends requests**: by user navigating address bar, or by JavaScript code (e.g., `fetch()` on button click).
2. **Waits for a reply**.
3. **Processes the reply**: either renders a full new page, or manipulates the current page (AJAX — Asynchronous JavaScript and XML).

---

## 5. HTTP Mechanics: Cookies and Sessions

Understanding cookies and sessions is essential for both development and security (see [[Supplementary - Web Application Security]]: ATT-6, ATT-7).

### Cookies

```
Server Response:  Set-Cookie: PHPSESSID=abc123; HttpOnly; Secure; SameSite=Strict
Browser Storage:  keyed by domain (and port)
Browser Action:   automatically includes Cookie: PHPSESSID=abc123 in every subsequent request
```

The cookie mechanism is automatic and invisible to the user. This is what enables session persistence — and what makes session hijacking possible when cookies are unprotected.

In PHP, cookies are managed with:
- `setcookie()` — set a cookie from the server
- `header("Set-Cookie: ...")` — manual header manipulation
- `$_COOKIE` — superglobal to read incoming cookies

### Sessions in PHP

PHP's session mechanism:
- **Session** = server-side storage space for one browser session
- Keyed by **`PHPSESSID`** (the session ID)
- Session data stored **at the server** (in `/tmp` by default, or a database)
- `PHPSESSID` transmitted to browser as a cookie

**Session lifecycle:**

```
1. session_start()       → creates or resumes a session
2. session_id()          → returns the current PHPSESSID
3. $_SESSION['key']      → read/write session data
4. session_regenerate_id(true) → critical on login (defeats session fixation)
5. session_destroy()     → invalidates the session (on logout)
```

**Login flow implementation:**
```php
session_start();
if (login_successful($username, $password)) {
    session_regenerate_id(true);          // defeat session fixation
    $_SESSION['username'] = $username;    // store authenticated state
    header("Location: home.php");
    exit();
}
```

**Session check on protected pages:**
```php
session_start();
if (!isset($_SESSION['username'])) {
    header("Location: signin.php");       // redirect unauthenticated users
    exit();
}
// serve protected content to $_SESSION['username']
```

---

## 6. HTTP Request Handling in PHP

### Request Methods

| Method | Purpose | PHP Access |
|---|---|---|
| `GET` | Retrieve data from server; parameters in URL query string | `$_GET['param']` |
| `POST` | Upload data to server; parameters in request body | `$_POST['param']` |

- Detect request method via `$_SERVER['REQUEST_METHOD']`.

### Ways to Send Requests from the Browser

| Mechanism | When Used |
|---|---|
| Address bar navigation | User explicitly types URL |
| HTML `<form>` element | Form submissions (login, registration, settings) |
| HTML `<img>`, `<script>` src attributes | Resources loaded automatically (also exploited in CSRF) |
| JavaScript `fetch()` function | AJAX requests (dynamic page updates without full reload) |

### PHP Superglobals Reference

| Superglobal | Contains |
|---|---|
| `$_GET` | URL query string parameters |
| `$_POST` | Form POST body parameters |
| `$_COOKIE` | All cookies sent by the browser |
| `$_SESSION` | Server-side session data for current PHPSESSID |
| `$_SERVER` | Request metadata (method, headers, server info) |

---

## 7. Password Security in PHP

Passwords must **never** be stored in plaintext. PHP provides built-in bcrypt functions:

```php
// Account creation: hash the plaintext password
$hash = password_hash($plaintext_password, PASSWORD_DEFAULT);
// Result: 60-character bcrypt hash stored in DB

// Login verification: compare plaintext against stored hash
$is_valid = password_verify($plaintext_password, $stored_hash);
// Returns: TRUE or FALSE
```

**Why bcrypt:**
- bcrypt is computationally expensive by design — brute-force attacks are slow.
- Each hash includes a unique salt — two identical passwords produce different hashes.
- `PASSWORD_DEFAULT` automatically uses the strongest available algorithm as PHP versions evolve.

---

## 8. PHP Development Concepts

### PHP Template (Dynamic vs Static)

PHP code is embedded in HTML using PHP tags (`<?php ... ?>`). The server executes PHP on every request; the browser receives only the resulting HTML.

```php
<!-- Static content (sent as-is): -->
<h1>Welcome</h1>

<!-- Dynamic content (executed on server, result sent): -->
<?php echo "Hello, " . $_SESSION['username']; ?>

<!-- JavaScript executes in the browser AFTER the server has sent the page -->
<script>alert("This runs in browser");</script>
```

Key distinction: **PHP execution = server side, at request time. JavaScript execution = browser side, after page load.**

### Page Navigation — PHP Redirection

```php
header("Location: /target-page.php");
exit();   // must call exit() to stop further PHP execution after redirect
```

### PHP File Content Reusage

```php
require 'config.php';        // fatal error if file not found
require_once 'config.php';   // include only once (prevents re-inclusion)
include 'header.php';        // warning if not found (non-fatal)
include_once 'header.php';   // include only once
```

### Debugging

- `phpinfo()` — displays all PHP configuration and environment information.
- Configure error reporting in `php.ini` for development vs production.

---

## 9. Database Layer: MySQL with PHP

### Setup Flow (Ubuntu)

```bash
# Install
sudo apt-get install mysql-server

# Access
mysql -u root -p

# Create DB and user
CREATE DATABASE socialnet;
CREATE USER 'webapp'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON socialnet.* TO 'webapp'@'localhost';
FLUSH PRIVILEGES;
```

- **Adminer**: lightweight web-based database management GUI (alternative to phpMyAdmin).
- Reconfigure MySQL to listen on a network socket for PHP-FPM to connect over TCP.

### SocialNet Database Schema

```sql
-- User accounts table
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

### Working with SELECT Queries (Parameterized)

```php
// Pattern: Open connection → Execute query → Fetch results (loop if multiple rows)
$pdo = new PDO("mysql:host=localhost;dbname=socialnet", $user, $pass);

// Parameterized query — safe against SQL injection
$stmt = $pdo->prepare("SELECT * FROM account WHERE username = ?");
$stmt->execute([$username]);
$row = $stmt->fetch(PDO::FETCH_ASSOC);   // one row
// or:
$rows = $stmt->fetchAll(PDO::FETCH_ASSOC);  // all rows (loop needed)
```

---

## 10. Server Environment: nginx + PHP-FPM

### Web Server vs Application Server

| Component | Role |
|---|---|
| **nginx** | Web server: receives HTTP requests; serves static files; proxies dynamic requests to PHP-FPM |
| **PHP-FPM** | PHP FastCGI Process Manager: executes PHP scripts; returns output to nginx |

### Key nginx Commands (Ubuntu)

```bash
# Install
sudo apt-get install nginx

# Control
sudo systemctl start nginx
sudo systemctl stop nginx
sudo systemctl status nginx

# Check listening ports
sudo ss -tlnp | grep nginx

# Configuration location
/etc/nginx/nginx.conf
/etc/nginx/sites-available/default    # default virtual server config
```

### nginx Document Root Concepts

- **Document root**: directory where nginx serves static files from.
- Default document root: `/var/www/html/`
- File ownership must match nginx's user account (typically `www-data`).

### PHP-FPM Key Commands

```bash
# Install
sudo apt-get install php-fpm

# Control
sudo systemctl start php8.1-fpm
sudo systemctl status php8.1-fpm

# Check processes
ps aux | grep php-fpm

# Check listening socket
sudo ss -tlnp | grep php
```

**nginx integration with PHP-FPM** (nginx config snippet):
```nginx
location ~ \.php$ {
    fastcgi_pass unix:/run/php/php8.1-fpm.sock;
    include fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
}
```

---

## 11. SocialNet Application — Page Transition Diagram

```
                    [not signed in]
                          │
              ┌─────► signin.php ◄─────────────┐
              │           │                     │
   Wrong      │    do signin successfully       │  Click "Logout"
  credentials │           │                     │  (session_destroy)
              │           ▼                     │
              └────── home.php ──────────────► signout.php
                          │
                          ├── make friend (NULL → friend relationship)
                          │
                          └──► setting.php (edit profile)
```

**Implementation sequence:**
1. **Admin form** → create initial user accounts (admin-only)
2. **signin.php** → login form (POST) → `password_verify()` → store username in `$_SESSION`
3. **home.php** → check `$_SESSION['username']`; if absent → redirect to `signin.php`
4. **signout.php** → `session_destroy()` → redirect to `signin.php`
5. **setting.php** → edit profile (protected; requires session check)
6. **profile.php** → view friend's profile (access control: must be friend)

---

## 12. Lab Exercises Summary

| Lab | Topic | Key Skills |
|---|---|---|
| Lab 1: Static Webserver | nginx control | install, start/stop, check processes and ports, config files, virtual servers, document root, ownership |
| Lab 2: Static Web on nginx | Serve HTML | edit HTML, copy to document root, set file ownership/mode, verify in browser |
| Lab 3: JavaScript | Frontend scripting | Follow W3Schools JS tutorial; DOM manipulation |
| Lab 4: PHP-FPM | Application server | install php-fpm, integrate with nginx, test with `phpinfo()`, helloworld PHP |

---

## Deep Dive: Why the Frontend/Backend Split Creates Security Complexity

The fundamental architectural fact — **frontend code runs on the client, backend code runs on the server** — has profound security implications that explain why every attack in [[Supplementary - Web Application Security]] is possible.

**The client is untrusted territory.** The browser is a device the attacker controls. Any data sent from the browser (forms, query strings, cookies, headers) must be treated as **potentially hostile input**. The backend can never assume:
- The data comes from its own legitimate frontend form.
- The data has not been modified between the browser and the server.
- The user sending the request is who they claim to be (just because they have a session cookie doesn't mean they weren't tricked into sending the request via CSRF).

This is why parameterized queries, CSRF tokens, output sanitization, and session regeneration are not optional hardening measures — they are the **required compensations** for the fundamental untrustworthiness of client-supplied data.

The security model for a web application is not "trust the browser" — it is **"verify everything on the server, trust nothing from the client."**

---

## Key Takeaways & Next Steps

1. **A web application is two programs** — frontend (browser) and backend (server) — connected by HTTP request-reply cycles. Security analysis must address both halves.
2. **PHP sessions use cookies** (`PHPSESSID`) to link browser state to server-side data — this is the exact mechanism exploited in ATT-6 and ATT-7.
3. **`session_regenerate_id(true)` on login** is a mandatory one-line security fix; without it, session fixation is trivial.
4. **`password_hash()` and `password_verify()`** are PHP's built-in bcrypt functions — always use them; never store or compare plaintext passwords.
5. **Parameterized queries** (`PDO::prepare()`) eliminate all three SQL injection attack variants from [[Supplementary - Web Application Security]] (ATT-3, ATT-4, ATT-5) with a single architectural choice.
6. **The browser is controlled by the attacker** — all backend code must validate, sanitize, and authorize on the server side, never trusting client-supplied data.

---

## Graph View Links

**Previous**: [[Module 8 - Network Security]]  
**Next**: [[Supplementary - Web Application Security]]  
**Hub**: [[CS451 - Hub]]
