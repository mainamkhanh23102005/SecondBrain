# Thực Hành 3 – T-SQL Nâng Cao: Các Hàm Quan Trọng

**Nguồn:** Hướng dẫn thực hành CSDL – Bài Thực Hành Số 3
**Tags:** #sql #t-sql #functions #string #datetime #numeric #cast #convert

---

## 1. Tổng Quan

T-SQL cung cấp hệ thống hàm tích hợp sẵn (built-in) để xử lý ba loại dữ liệu phổ biến:

| Nhóm | Các hàm chính |
|------|---------------|
| Số | `ISNUMERIC`, `ROUND` |
| Chuỗi | `LEFT`, `RIGHT`, `SUBSTRING`, `LEN`, `REPLACE`, `STUFF`, `LOWER`, `UPPER`, `LTRIM`, `RTRIM` |
| Ngày/Giờ | `GETDATE`, `DAY`, `MONTH`, `YEAR`, `DATEPART`, `DATENAME` |
| Chuyển đổi kiểu | `CAST`, `CONVERT` |

---

## 2. Hàm Số (Numeric Functions)

### 2.1 ISNUMERIC

```sql
ISNUMERIC(biểu_thức)
-- Trả về 1 nếu biểu_thức có thể chuyển sang kiểu số, 0 nếu không
```

```sql
SELECT HOTEN, ISNUMERIC(MACT) AS ISNUMERIC
FROM CAUTHU
```

**Logic:** Hàm kiểm tra xem chuỗi có thể parse thành số hay không. Hữu ích để validate dữ liệu nhập vào trước khi thực hiện phép tính. Lưu ý: `ISNUMERIC('$5')` trả về 1 vì `$` là ký hiệu tiền tệ hợp lệ — hàm này khá "rộng rãi" trong định nghĩa "số".

---

### 2.2 ROUND

```sql
ROUND(số_làm_tròn, độ_dài_làm_tròn [, hàm])
```

| Ví dụ | Kết quả | Giải thích |
|-------|---------|-----------|
| `ROUND(123.9994, 3)` | `123.999` | Làm tròn đến 3 chữ số thập phân |
| `ROUND(123.9995, 3)` | `124.000` | Chữ số thứ 4 = 5, làm tròn lên |
| `ROUND(123.4545, 2)` | `123.450` | Làm tròn đến 2 chữ số thập phân |
| `ROUND(123.45, -2)` | `100.00` | Âm = làm tròn sang trái dấu thập phân |
| `ROUND(150.75, 0)` | `151.00` | Làm tròn đến hàng đơn vị |
| `ROUND(150.75, 0, 1)` | `150.00` | Tham số thứ 3 ≠ 0: cắt bỏ (truncate), không làm tròn |

**Logic của `độ_dài_làm_tròn` âm:**
- `-1`: làm tròn đến hàng chục → `ROUND(456, -1)` = `460`
- `-2`: làm tròn đến hàng trăm → `ROUND(456, -2)` = `500`
- Nếu giá trị âm lớn hơn số chữ số trước dấu thập phân → trả về 0.

---

## 3. Hàm Chuỗi (String Functions)

### 3.1 LEFT và RIGHT

```sql
LEFT(chuỗi, n)   -- lấy n ký tự từ bên trái
RIGHT(chuỗi, n)  -- lấy n ký tự từ bên phải
```

```sql
SELECT LEFT('Nha Trang', 5)    -- 'Nha T'
SELECT RIGHT('Nha Trang', 5)   -- 'Trang'
```

**Logic:** Đây là trường hợp đặc biệt của SUBSTRING. `LEFT(s, n)` = `SUBSTRING(s, 1, n)`. `RIGHT(s, n)` = `SUBSTRING(s, LEN(s) - n + 1, n)`.

---

### 3.2 SUBSTRING

```sql
SUBSTRING(chuỗi, vị_trí_bắt_đầu, chiều_dài)
-- vị_trí_bắt_đầu: 1-based (ký tự đầu tiên là vị trí 1)
```

```sql
SELECT SUBSTRING('Nha Trang', 2, 5)   -- 'ha Tr' (từ vị trí 2, lấy 5 ký tự)
SELECT SUBSTRING('Nha Trang', -2, 5)  -- 'Nha' (vị trí âm: bắt đầu từ đầu chuỗi)
```

**Logic vị trí âm:** Nếu `vị_trí_bắt_đầu` âm hoặc bằng 0, SQL Server tự điều chỉnh — cắt bớt `chiều_dài` đi phần trước vị trí 1. Kết quả có thể ngắn hơn `chiều_dài` yêu cầu.

---

### 3.3 LEN

```sql
LEN(chuỗi)  -- trả về số ký tự, KHÔNG tính khoảng trắng ở cuối
```

```sql
SELECT LEN('Nha Trang')   -- 9
SELECT LEN('Nha Trang  ') -- cũng 9 (khoảng trắng cuối bị bỏ qua)
```

**Lưu ý:** `LEN` bỏ qua trailing spaces. Dùng `DATALENGTH` nếu cần đếm chính xác byte (kể cả khoảng trắng cuối).

---

### 3.4 REPLACE

```sql
REPLACE(chuỗi_gốc, chuỗi_cũ, chuỗi_mới)
-- Thay TẤT CẢ lần xuất hiện của chuỗi_cũ bằng chuỗi_mới
```

```sql
SELECT REPLACE('Nha Trang', 'Nha', 'nha')  -- 'nha Trang'
SELECT REPLACE(VITRI, N'Tiền', N'tiền') FROM CAUTHU
```

**Logic:** REPLACE thực hiện case-sensitive theo collation của database. Nếu collation là `CI` (Case Insensitive) thì không phân biệt hoa/thường. Thay toàn bộ, không giới hạn lần xuất hiện.

---

### 3.5 STUFF

```sql
STUFF(chuỗi_gốc, vị_trí_bắt_đầu, số_ký_tự_xóa, chuỗi_thay_thế)
```

```sql
SELECT STUFF('Nha Trang', 2, 3, '***')
-- Bắt đầu tại vị trí 2, xóa 3 ký tự ('ha '), chèn '***'
-- Kết quả: 'N***Trang'
```

**So sánh REPLACE vs STUFF:**
| | REPLACE | STUFF |
|-|---------|-------|
| Xác định vị trí | Không (tìm theo nội dung) | Có (tìm theo vị trí số) |
| Thay tất cả lần xuất hiện | Có | Không (chỉ một chỗ) |
| Dùng khi | Không biết vị trí chính xác | Biết vị trí, muốn thay/xóa theo vị trí |

---

### 3.6 LOWER / UPPER

```sql
LOWER(chuỗi)  -- chuyển toàn bộ thành chữ thường
UPPER(chuỗi)  -- chuyển toàn bộ thành chữ hoa
```

```sql
SELECT LOWER('Nha Trang'), UPPER('Nha Trang')
-- 'nha trang' | 'NHA TRANG'
```

**Dùng khi:** So sánh chuỗi không phân biệt hoa/thường trong collation CS (Case Sensitive): `WHERE LOWER(HOTEN) = LOWER(@input)`.

---

### 3.7 LTRIM / RTRIM

```sql
LTRIM(chuỗi)  -- cắt khoảng trắng bên trái
RTRIM(chuỗi)  -- cắt khoảng trắng bên phải
-- TRIM() đầy đủ hai phía: LTRIM(RTRIM(chuỗi))
```

```sql
DECLARE @llen INT, @rlen INT, @len INT
SELECT @llen = LEN(LTRIM(' Nha Trang')),   -- 9 (bỏ khoảng trắng trái)
       @rlen = LEN(RTRIM('Nha Trang  ')),  -- 9 (bỏ khoảng trắng phải)
       @len  = LEN('Nha Trang')            -- 9
SELECT @llen, @rlen, @len
```

**Logic:** `LTRIM` loại khoảng trắng (space, tab?) ở đầu. Thường dùng kết hợp: `LTRIM(RTRIM(col))` để làm sạch dữ liệu nhập vào. SQL Server 2017+ có `TRIM()` làm cả hai phía.

---

## 4. Hàm Ngày/Giờ (Date/Time Functions)

### 4.1 GETDATE

```sql
GETDATE()  -- trả về ngày giờ hiện tại của server
```

```sql
SELECT GETDATE()  -- VD: 2026-05-10 11:30:45.123
```

**Logic:** Trả về kiểu `DATETIME` chính xác đến millisecond. Đây là "đồng hồ" của SQL Server, không phải của client. Dùng làm giá trị mặc định cho cột tạo-ngày: `DEFAULT GETDATE()`.

---

### 4.2 DAY / MONTH / YEAR

```sql
DAY(datetime_value)    -- trả về ngày (1-31)
MONTH(datetime_value)  -- trả về tháng (1-12)
YEAR(datetime_value)   -- trả về năm (4 chữ số)
```

```sql
SELECT HOTEN,
       DAY(NGAYSINH)   AS [Ngày sinh],
       MONTH(NGAYSINH) AS [Tháng sinh],
       YEAR(NGAYSINH)  AS [Năm sinh]
FROM CAUTHU
WHERE MACT = 5

-- Tính tuổi:
WHERE YEAR(GETDATE()) - YEAR(NGAYSINH) > 20
```

**Lưu ý tính tuổi:** `YEAR(GETDATE()) - YEAR(NGAYSINH)` chỉ lấy năm, không tính tháng/ngày sinh. Người sinh 31/12/2000 và 01/01/2000 đều cho cùng kết quả khi tính theo cách này. Dùng `DATEDIFF(YEAR, NGAYSINH, GETDATE())` chính xác hơn.

---

### 4.3 DATEPART

```sql
DATEPART(đơn_vị_thời_gian, datetime_value)
-- Trả về số nguyên
```

| Đơn vị | Viết tắt | Ý nghĩa |
|--------|----------|---------|
| Năm | `yy`, `yyyy` | 4 chữ số năm |
| Quý | `qq`, `q` | 1-4 |
| Tháng | `mm`, `m` | 1-12 |
| Số ngày trong năm | `dy`, `y` | 1-366 |
| Ngày | `dd`, `d` | 1-31 |
| Tuần trong năm | `wk`, `ww` | 1-53 |
| Ngày trong tuần | `dw` | 1=CN, 2=T2, ..., 7=T7 (tùy cài đặt DATEFIRST) |
| Giờ | `hh` | 0-23 |
| Phút | `mi`, `n` | 0-59 |
| Giây | `ss`, `s` | 0-59 |

```sql
SELECT DATEPART(yyyy, NGAYSINH) AS NAMSINH,
       DATEPART(qq, NGAYSINH)   AS QUYSINH,
       DATEPART(m, NGAYSINH)    AS THANGSINH,
       DATEPART(wk, NGAYSINH)   AS TUANSINH,
       DATEPART(d, NGAYSINH)    AS NGAYSINH,
       DATEPART(dy, NGAYSINH)   AS NGAY_TRONG_NAM,
       DATEPART(dw, NGAYSINH)   AS NGAY_TRONG_TUAN
FROM CAUTHU
WHERE MACT = 5
```

**Logic:** `DATEPART` trả về số nguyên. Khi cần lấy quý, tuần — đây là hàm duy nhất có thể làm được, không có hàm `QUARTER()` hay `WEEK()` riêng biệt trong T-SQL cũ.

---

### 4.4 DATENAME

```sql
DATENAME(đơn_vị_thời_gian, datetime_value)
-- Tương tự DATEPART nhưng trả về CHUỖI (tên)
```

```sql
SELECT DATENAME(yyyy, NGAYSINH) AS NAMSINH,   -- '2000'
       DATENAME(mm, NGAYSINH)   AS THANGSINH,  -- 'January' (hoặc tháng tùy locale)
       DATENAME(dw, NGAYSINH)   AS NGAY_TRONG_TUAN  -- 'Monday'
FROM CAUTHU
WHERE MACT = 5
```

**DATEPART vs DATENAME:**
| | DATEPART | DATENAME |
|-|----------|----------|
| Kiểu trả về | INT | NVARCHAR |
| `mm` | `5` | `'May'` |
| `dw` | `2` | `'Monday'` |
| Dùng khi | Tính toán, so sánh | Hiển thị thân thiện |

---

## 5. Hàm Chuyển Đổi Kiểu: CAST và CONVERT

### 5.1 CAST

```sql
CAST(biểu_thức AS kiểu_dữ_liệu[(độ_dài)])
```

```sql
CAST(NGAYSINH AS VARCHAR(20))  -- chuyển datetime sang chuỗi
CAST('123' AS INT)             -- chuyển chuỗi sang số
```

**Logic:** CAST là cú pháp SQL chuẩn (ANSI). Không kiểm soát được định dạng đầu ra khi chuyển datetime sang chuỗi — SQL Server dùng định dạng mặc định.

---

### 5.2 CONVERT

```sql
CONVERT(kiểu_dữ_liệu[(độ_dài)], biểu_thức [, style])
```

Tham số `style` kiểm soát **định dạng ngày tháng** khi chuyển datetime ↔ varchar:

| Style | Định dạng | Ví dụ |
|-------|-----------|-------|
| `0` hoặc `100` | `mon dd yyyy hh:miAM` | `May 10 2026 11:30AM` |
| `1` / `101` | `mm/dd/yy` / `mm/dd/yyyy` | `05/10/26` / `05/10/2026` |
| `3` / `103` | `dd/mm/yy` / `dd/mm/yyyy` | `10/05/26` / `10/05/2026` ← Việt Nam |
| `4` / `104` | `dd.mm.yy` / `dd.mm.yyyy` | `10.05.26` / `10.05.2026` |
| `108` | `hh:mm:ss` | `11:30:45` |
| `112` | `yyyymmdd` | `20260510` |

```sql
-- Hiển thị ngày theo định dạng Việt Nam dd/mm/yyyy:
SELECT HOTEN,
       CONVERT(VARCHAR, NGAYSINH, 103) AS NGAYSINH,
       VITRI
FROM CAUTHU
WHERE YEAR(GETDATE()) - YEAR(NGAYSINH) > 20
```

**Logic style 103:** `103` = `100 + 3`, số 100+ có nghĩa là năm 4 chữ số. Không có 100+ → năm 2 chữ số.

**CAST vs CONVERT — khi nào dùng gì?**
| | CAST | CONVERT |
|-|------|---------|
| Chuẩn SQL | Có (ANSI) | Chỉ SQL Server / Sybase |
| Kiểm soát format ngày | Không | Có (tham số style) |
| Khuyến nghị | Khi không cần format | Khi cần format datetime |

---

## 6. Kết Hợp Các Hàm

Các hàm có thể lồng nhau để giải quyết bài toán phức tạp:

```sql
-- Lấy 5 ký tự đầu của chuỗi đã chuyển thường:
SELECT LEFT(LOWER(HOTEN), 5) FROM CAUTHU

-- Format ngày và lọc theo tuổi:
SELECT HOTEN,
       CONVERT(VARCHAR, NGAYSINH, 103) AS NgaySinh_Format
FROM CAUTHU
WHERE YEAR(GETDATE()) - YEAR(NGAYSINH) BETWEEN 20 AND 30

-- Đếm ký tự sau khi trim:
SELECT LEN(LTRIM(RTRIM(HOTEN))) AS DoiDaiThucSu FROM CAUTHU

-- Thay thế và kiểm tra độ dài:
SELECT REPLACE(VITRI, N'Tiền', N'tiền'),
       LEN(VITRI) AS ChieuDaiGoc
FROM CAUTHU
```

---

## Tóm Tắt Nhanh

| Hàm | Cú pháp ngắn | Trả về |
|-----|-------------|--------|
| ISNUMERIC | `ISNUMERIC(x)` | 0 hoặc 1 |
| ROUND | `ROUND(x, n)` | Số đã làm tròn |
| LEFT / RIGHT | `LEFT(s, n)` | Chuỗi con |
| SUBSTRING | `SUBSTRING(s, pos, len)` | Chuỗi con |
| LEN | `LEN(s)` | Số nguyên (độ dài) |
| REPLACE | `REPLACE(s, old, new)` | Chuỗi mới |
| STUFF | `STUFF(s, pos, del, ins)` | Chuỗi mới |
| LOWER / UPPER | `LOWER(s)` | Chuỗi đã đổi case |
| LTRIM / RTRIM | `LTRIM(s)` | Chuỗi đã bỏ khoảng trắng |
| GETDATE | `GETDATE()` | DATETIME hiện tại |
| DAY/MONTH/YEAR | `YEAR(d)` | INT |
| DATEPART | `DATEPART(yy, d)` | INT |
| DATENAME | `DATENAME(mm, d)` | NVARCHAR |
| CAST | `CAST(x AS type)` | Kiểu mới |
| CONVERT | `CONVERT(type, x, style)` | Kiểu mới (có format) |
