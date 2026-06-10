# Exam Study — Lab 4.1: Web Application Environment Setup

**Source:** Practical Experience Report — Lab 4.1 (nginx + PHP-FPM + MySQL on Ubuntu 24.04)
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]
**Tags:** #CS451 #exam #lab #nginx #php-fpm #mysql #web-deployment

---

## Quick Lookup Index

**Sections:**
1. The Stack (nginx + PHP-FPM + MySQL)
2. nginx — Static Web Server
3. nginx Configuration Workflow
4. PHP-FPM — Application Server
5. nginx ↔ PHP-FPM Integration
6. MySQL — Database Server
7. MySQL CLI & Adminer
8. Deep Dive: Why Three Separate Processes

**Key Terms:** nginx, port 80, `www-data`, `master/worker` process, PHP-FPM, `php8.3-fpm`, FastCGI, `.sock` socket, `fastcgi_pass`, `/etc/nginx/sites-available/default`, `document root`, `location` block, virtual server, `nginx -t`, `nginx -s reload`, `phpinfo()`, MySQL, port 3306, `bind-address`, `mysqld.cnf`, `GRANT`, Adminer, `ss -tlnp`

---

## 1. The Stack

| Layer | Software | Role | Default Port |
|---|---|---|---|
| **Web server** | **nginx** | Serves static files; reverse-proxies dynamic requests to PHP-FPM | TCP **80** |
| **App server** | **PHP-FPM** (`php8.3-fpm`) | Executes PHP code via FastCGI | Unix socket (`.sock`) |
| **Database** | **MySQL** (`mysql`) | Stores application data | TCP **3306** |

**Process model (all three):** a **master** process runs as **root**; **worker** processes run as **`www-data`** (least-privilege service account).

---

## 2. nginx — Static Web Server

| Task | Command |
|---|---|
| Install | `sudo apt update && sudo apt install nginx -y` |
| Start / Stop | `sudo systemctl start nginx` / `sudo systemctl stop nginx` |
| Check port & protocol | `sudo ss -tlnp | grep nginx` → port **80 / TCP** |
| Which account it runs as | `ps aux | grep nginx` → master=**root**, workers=**www-data** |

---

## 3. nginx Configuration Workflow

**Config file:** `/etc/nginx/sites-available/default`

**Typical change cycle (always test before reload!):**
```bash
sudo nano /etc/nginx/sites-available/default   # 1. edit
sudo nginx -t                                  # 2. test syntax (won't crash server)
sudo systemctl reload nginx                    # 3. apply (or: sudo nginx -s reload)
```

**Configurable items practiced in the lab:**
- Test with a static `hello.txt` and `hello.html`
- Change the **listening port** (`listen 80;` → another port)
- Change the **document root** (`root /var/www/html;`)
- Add a new **`location`** block
- Add a second **virtual server** listening on another port

---

## 4. PHP-FPM — Application Server

**PHP-FPM (FastCGI Process Manager)** — runs PHP code; nginx itself cannot execute PHP, so it hands `.php` requests to PHP-FPM over a socket.

| Task | Command |
|---|---|
| Install | `sudo apt update && sudo apt install php-fpm -y` |
| Exact service name (Ubuntu 24.04) | **`php8.3-fpm`** |
| Start / Stop / Restart | `sudo systemctl start|stop|restart php8.3-fpm` |
| Which account | `ps aux | grep php-fpm` → master=**root**, pool workers=**www-data** |

---

## 5. nginx ↔ PHP-FPM Integration

**Add this `location` block inside the `server { ... }` block** of `/etc/nginx/sites-available/default`:
```nginx
location ~ \.php$ {
    include snippets/fastcgi-php.conf;
    fastcgi_pass unix:/var/run/php/php8.3-fpm.sock;
}
```
- `location ~ \.php$` — match any request ending in `.php`.
- `fastcgi_pass unix:.../php8.3-fpm.sock` — forward it to PHP-FPM over its Unix socket.

**Test file** (`/var/www/html/info.php`):
```php
<?php
phpinfo();
?>
```
| Property | Value |
|---|---|
| Location | `/var/www/html/info.php` |
| Ownership | `www-data:www-data` → `sudo chown www-data:www-data /var/www/html/info.php` |
| Mode | `644` (`-rw-r--r--`) → `sudo chmod 644 /var/www/html/info.php` |

> `phpinfo()` renders the full PHP configuration page — proves nginx→PHP-FPM integration works.

---

## 6. MySQL — Database Server

| Task | Command |
|---|---|
| Install | `sudo apt update && sudo apt install mysql-server -y` |
| Service name | **`mysql`** |
| Start / Stop / Restart | `sudo systemctl start|stop|restart mysql` |
| Check listening address/port | `sudo ss -tlnp | grep mysql` → `127.0.0.1:3306` by default |

**Listen on all interfaces** (so other hosts can connect):
- File: `/etc/mysql/mysql.conf.d/mysqld.cnf`
- Directive: change `bind-address = 127.0.0.1` → `bind-address = 0.0.0.0`
- **After change:** `sudo systemctl restart mysql` (re-binds the network socket)

> Security note: `0.0.0.0` exposes MySQL to the network — only do this when needed, and pair with a firewall + least-privilege DB users.

---

## 7. MySQL CLI & Adminer

```bash
sudo -i          # become root
mysql            # open MySQL session
```
```sql
SHOW DATABASES;                                  -- list databases
USE socialnet;                                   -- select a database
SHOW TABLES;                                      -- list tables
CREATE USER 'appuser'@'localhost' IDENTIFIED BY 'StrongP@ss';   -- create user + password
GRANT ALL PRIVILEGES ON socialnet.* TO 'appuser'@'localhost';   -- grant privileges
FLUSH PRIVILEGES;
EXIT;                                             -- leave session
```

**Adminer** — lightweight single-file web DB admin tool. Install, browse to it, create a database + table via the GUI to verify MySQL works.

---

## 8. Deep Dive: Why Three Separate Processes

**Separation of concerns.** nginx is optimized for fast, concurrent handling of network connections and static files; it deliberately *cannot* execute PHP. PHP-FPM is a separate pool of PHP workers tuned for script execution. MySQL is a separate storage engine. Splitting them means each can be scaled, restarted, and secured independently — and a crash or compromise in one is contained.

**Why the master/worker + `www-data` split matters.** The master starts as **root** only to bind privileged resources (port 80, the socket). It then spawns **workers as `www-data`**, an unprivileged account. If an attacker compromises a worker (e.g. via a PHP bug), they get only `www-data` rights — not root. This is **privilege separation** in action, the same principle as least-privilege DB users.

**FastCGI socket, not a port.** nginx talks to PHP-FPM over a **Unix domain socket** (`php8.3-fpm.sock`) rather than a TCP port. Unix sockets are faster (no TCP stack overhead) and not network-exposed by default — PHP execution can't be reached directly from outside, only through nginx.

**`nginx -t` before reload.** A syntax error in the config would crash nginx on restart, taking the site down. `nginx -t` validates the config first; `reload` then applies it gracefully without dropping existing connections. This is the safe change discipline you'd replicate in any production deployment.

**`bind-address` and exposure.** MySQL defaulting to `127.0.0.1` means it's only reachable from the same host — the most secure default for a single-box deployment (app and DB co-located). Changing to `0.0.0.0` is necessary only for a separate DB server, and immediately widens the attack surface, which is why it must be paired with firewall rules and restricted DB accounts.

---

## Lab Playbook (Copy-Paste)

```bash
# ---------- nginx ----------
sudo apt update && sudo apt install nginx -y
sudo systemctl start nginx
sudo ss -tlnp | grep nginx          # port 80/TCP
ps aux | grep nginx                 # master=root, workers=www-data
sudo nano /etc/nginx/sites-available/default
sudo nginx -t                       # ALWAYS test before reload
sudo systemctl reload nginx         # or: sudo nginx -s reload

# ---------- PHP-FPM ----------
sudo apt update && sudo apt install php-fpm -y
sudo systemctl restart php8.3-fpm
ps aux | grep php-fpm

# nginx<->php-fpm: add inside server { } block:
#   location ~ \.php$ {
#       include snippets/fastcgi-php.conf;
#       fastcgi_pass unix:/var/run/php/php8.3-fpm.sock;
#   }

# test file
echo '<?php phpinfo(); ?>' | sudo tee /var/www/html/info.php
sudo chown www-data:www-data /var/www/html/info.php
sudo chmod 644 /var/www/html/info.php
# browse to http://<vm-ip>/info.php

# ---------- MySQL ----------
sudo apt update && sudo apt install mysql-server -y
sudo systemctl start mysql
sudo ss -tlnp | grep mysql          # 127.0.0.1:3306
# listen on all interfaces:
sudo nano /etc/mysql/mysql.conf.d/mysqld.cnf   # bind-address = 0.0.0.0
sudo systemctl restart mysql

# MySQL session
sudo -i
mysql
#   SHOW DATABASES;
#   CREATE DATABASE socialnet;
#   USE socialnet;
#   SHOW TABLES;
#   CREATE USER 'appuser'@'localhost' IDENTIFIED BY 'StrongP@ss';
#   GRANT ALL PRIVILEGES ON socialnet.* TO 'appuser'@'localhost';
#   FLUSH PRIVILEGES;
#   EXIT;
```

---

## Knowledge Check Q&A

**Q1:** What port and protocol does nginx listen on by default?
**A:** TCP port **80**.

**Q2:** Under which accounts do the nginx master and worker processes run?
**A:** Master = **root**, workers = **www-data**.

**Q3:** Why can't nginx serve PHP on its own, and how is it solved?
**A:** nginx only serves static content; it forwards `.php` requests to **PHP-FPM** over a FastCGI Unix socket via a `location ~ \.php$ { fastcgi_pass ... }` block.

**Q4:** What is the exact PHP-FPM service name on Ubuntu 24.04, and what's its socket path?
**A:** Service `php8.3-fpm`; socket `/var/run/php/php8.3-fpm.sock`.

**Q5:** What two steps should you always do before reloading nginx after a config edit?
**A:** Run `sudo nginx -t` to test syntax, then `sudo systemctl reload nginx` only if it passes.

**Q6:** How do you make MySQL listen on all interfaces, and what must you do after?
**A:** Set `bind-address = 0.0.0.0` in `/etc/mysql/mysql.conf.d/mysqld.cnf`, then `sudo systemctl restart mysql`.

---

## Graph View Links

**Previous**: [[Exam Study - Lab 3 (Linux System Hardening)]]
**Next**: [[Exam Study - SocialNet Security Lab (ATT-1 to ATT-7)]]
**Hub**: [[CS451 - Hub]]
**Related**: [[Exam Study - Web Application Development]]
