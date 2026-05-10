# Thực Hành 2 – Thao Tác Dữ Liệu Với T-SQL Cơ Bản

**Nguồn:** Hướng dẫn thực hành CSDL – Bài Thực Hành Số 2
**Tags:** #sql #t-sql #database #dml #ddl #select #join

---

## 1. Tổng Quan Về SQL và T-SQL

**SQL (Structured Query Language)** là ngôn ngữ khai báo — bạn chỉ cần *mô tả muốn lấy gì*, không cần chỉ định *lấy như thế nào*. Máy chủ tự tìm đường thực thi tối ưu.

**T-SQL (Transact-SQL)** là phần mở rộng của Microsoft dành cho SQL Server, bổ sung thêm: biến, vòng lặp, điều kiện, hàm, stored procedure, trigger.

T-SQL chia thành 3 nhóm lệnh:

| Nhóm | Viết tắt | Mục đích | Ví dụ lệnh |
|------|----------|----------|------------|
| Định nghĩa dữ liệu | DDL | Tạo/thay đổi/xóa cấu trúc | CREATE, ALTER, DROP |
| Điều khiển truy cập | DCL | Phân quyền | GRANT, DENY, REVOKE |
| Thao tác dữ liệu | DML | Đọc/ghi dữ liệu | SELECT, INSERT, UPDATE, DELETE |

---

## 2. DML – Ngôn Ngữ Thao Tác Dữ Liệu

### 2.1 Cú Pháp Đầy Đủ Của SELECT

```sql
SELECT [ALL | DISTINCT] [TOP n]  danh_sách_cột
  INTO tên_bảng_mới          -- tùy chọn: tạo bảng mới từ kết quả
  FROM danh_sách_bảng
 [WHERE điều_kiện]
 [GROUP BY danh_sách_cột]
 [HAVING điều_kiện_nhóm]
 [ORDER BY cột [ASC|DESC]]
```

> **Logic thực thi bên trong SQL Server (thứ tự xử lý thực):**
> `FROM` → `WHERE` → `GROUP BY` → `HAVING` → `SELECT` → `ORDER BY`
> Dù bạn viết SELECT lên đầu, nó được xử lý **gần cuối**. Điều này giải thích tại sao bạn **không thể dùng alias cột trong WHERE** (WHERE chạy trước SELECT).

---

### 2.2 Danh Sách Chọn (SELECT List)

#### Chọn tất cả cột
```sql
SELECT * FROM CAUTHU
```
`*` lấy toàn bộ cột theo thứ tự định nghĩa bảng. Nên tránh trong production vì: lãng phí băng thông, dễ vỡ khi bảng thêm cột.

#### Chọn cột cụ thể và đặt alias
```sql
SELECT [Mã cầu thủ] = MACT,
       HOTEN         AS [Tên cầu thủ],
       VITRI         [Vị trí]
FROM CAUTHU
```
Ba cách đặt alias đều hợp lệ. Alias có khoảng trắng cần bọc trong `[]` hoặc `''`.

#### DISTINCT – Loại bỏ dòng trùng
```sql
SELECT DISTINCT MACLB1 FROM TRANDAU
```
**Logic:** SQL Server dùng sort hoặc hash để gom các giá trị giống nhau, chỉ giữ một. Tốn thêm CPU nếu bảng lớn.

#### TOP n – Giới hạn số dòng
```sql
SELECT TOP 7 HOTEN FROM CAUTHU
SELECT TOP 10 PERCENT HOTEN FROM CAUTHU
```
Không có `ORDER BY` thì thứ tự TOP là tùy ý (engine quyết định). Luôn kết hợp `ORDER BY` nếu muốn kết quả xác định.

#### CASE...WHEN – Cột tính toán có điều kiện
```sql
SELECT HOTEN,
       CASE GENDER
           WHEN 1 THEN 'NAM'
           ELSE N'NỮ'
       END AS [GIỚI TÍNH]
FROM CAUTHU
```
**Logic:** CASE được đánh giá hàng-theo-hàng tại thời điểm SELECT chạy. Dạng `CASE biểu_thức WHEN giá_trị` so sánh bằng. Dạng `CASE WHEN điều_kiện` cho phép so sánh phức tạp hơn.

---

### 2.3 Mệnh Đề WHERE – Lọc Dữ Liệu

```sql
SELECT HOTEN FROM CAUTHU WHERE MACT > 2
```

#### Các toán tử so sánh
| Toán tử | Ý nghĩa |
|---------|---------|
| `=` | Bằng |
| `<>` hoặc `!=` | Khác |
| `>`, `<`, `>=`, `<=` | Lớn/nhỏ hơn |
| `!>` | Không lớn hơn (tương đương `<=`) |
| `!<` | Không nhỏ hơn (tương đương `>=`) |

#### BETWEEN – Kiểm tra khoảng
```sql
WHERE year(getdate()) - year(NGAYSINH) BETWEEN 20 AND 25
```
**Logic:** `BETWEEN a AND b` tương đương `>= a AND <= b`, **bao gồm cả 2 đầu mút**. Dùng với số, ngày, chuỗi đều được.

#### IN / NOT IN – Kiểm tra tập hợp
```sql
WHERE MACT IN (4, 6, 7)

-- IN với subquery:
WHERE MACLB NOT IN (SELECT MACLB1 FROM TRANDAU)
```
**Logic:** `IN (danh sách)` SQL Server dịch thành chuỗi `OR`. `IN (subquery)` thường được tối ưu thành semi-join nội bộ.
**Cẩn thận:** `NOT IN` với subquery trả về NULL sẽ không trả về dòng nào (vì `x <> NULL` luôn là UNKNOWN). Dùng `NOT EXISTS` an toàn hơn.

#### LIKE – Khớp chuỗi mẫu
| Ký tự đại diện | Ý nghĩa |
|----------------|---------|
| `%` | Chuỗi bất kỳ (0 hoặc nhiều ký tự) |
| `_` | Đúng 1 ký tự bất kỳ |
| `[a-f]` | Một ký tự trong tập {a,b,c,d,e,f} |
| `[^a-f]` | Một ký tự **ngoài** tập đó |

```sql
WHERE HOTEN LIKE N'Nguyễn %'   -- tên bắt đầu bằng "Nguyễn "
```

#### IS NULL / IS NOT NULL
```sql
WHERE DIENTHOAI IS NULL
```
**Quan trọng:** NULL không so sánh bằng `=`. `WHERE col = NULL` luôn trả về 0 dòng vì NULL là "không biết" — so sánh với không biết cũng ra không biết (UNKNOWN ≠ TRUE).

---

### 2.4 ORDER BY – Sắp Xếp Kết Quả

```sql
SELECT HOTEN,
       year(getdate()) - year(NGAYSINH) AS AGE,
       VITRI
FROM CAUTHU
ORDER BY AGE DESC          -- sắp xếp theo tuổi giảm dần
ORDER BY 2 DESC            -- cách thay thế: dùng số thứ tự cột
```
**Logic:** ORDER BY là bước cuối cùng. Có thể ORDER BY theo alias (vì alias đã được xác định ở bước SELECT). Mặc định là ASC.

---

### 2.5 UNION – Gộp Kết Quả Nhiều Truy Vấn

```sql
SELECT A, B FROM BangA
UNION
SELECT F, G FROM BangB
```

**Quy tắc bắt buộc:**
1. Số cột phải bằng nhau giữa các truy vấn con.
2. Kiểu dữ liệu các cột tương ứng phải tương thích.
3. Tên cột kết quả lấy theo truy vấn **đầu tiên**.

**UNION vs UNION ALL:**
- `UNION`: tự động loại bỏ dòng trùng (tốn thêm sort/hash).
- `UNION ALL`: giữ lại toàn bộ, nhanh hơn.

**Hạn chế:**
- `ORDER BY` chỉ được đặt **sau câu UNION cuối**, không được đặt trong từng truy vấn con.
- Không dùng được trong `CREATE VIEW`.

---

### 2.6 JOIN – Phép Nối Bảng

Khi cần dữ liệu từ nhiều bảng, phải dùng JOIN để ghép các dòng theo điều kiện.

#### INNER JOIN (Phép nối trong)
Chỉ trả về dòng **khớp ở cả hai bảng**.
```sql
-- Cú pháp cũ (WHERE):
SELECT HOTEN, VITRI, TENCLB
FROM CAUTHU ct, CAULACBO clb
WHERE ct.MACLB = clb.MACLB

-- Cú pháp SQL-92 (khuyến nghị):
SELECT HOTEN, VITRI, TENCLB
FROM CAUTHU ct
INNER JOIN CAULACBO clb ON ct.MACLB = clb.MACLB
```
**Logic:** SQL Server so sánh từng dòng CAUTHU với từng dòng CAULACBO, giữ lại cặp nào thỏa `ct.MACLB = clb.MACLB`. Cầu thủ không thuộc CLB nào sẽ **bị loại**.

#### LEFT JOIN (Phép nối ngoài trái)
Trả về **tất cả dòng bảng trái**, dù không có cặp khớp bên phải (cột bên phải sẽ là NULL).
```sql
SELECT HOTEN, VITRI, TENCLB
FROM CAUTHU ct
LEFT JOIN CAULACBO clb ON ct.MACLB = clb.MACLB
```
**Dùng khi:** Muốn lấy toàn bộ cầu thủ kể cả những cầu thủ chưa có câu lạc bộ.

#### RIGHT JOIN – Ngược lại LEFT JOIN
```sql
SELECT HOTEN, VITRI, TENCLB
FROM CAUTHU ct
RIGHT JOIN CAULACBO clb ON ct.MACLB = clb.MACLB
```
Trả về tất cả CLB, kể cả CLB không có cầu thủ nào (cột HOTEN sẽ NULL).

#### FULL JOIN (Phép nối đầy đủ)
Trả về tất cả dòng của **cả hai bảng**, NULL ở phía không có cặp.
```sql
SELECT HOTEN, VITRI, TENCLB
FROM CAUTHU ct
FULL JOIN CAULACBO clb ON ct.MACLB = clb.MACLB
```

#### Self JOIN (Tự nối)
Nối một bảng với chính nó. Phải dùng alias khác nhau.
```sql
SELECT MATRAN,
       clb1.TENCLB AS [Tên CLB 1],
       clb2.TENCLB AS [Tên CLB 2]
FROM TRANDAU td
JOIN CAULACBO clb1 ON td.MACLB1 = clb1.MACLB
JOIN CAULACBO clb2 ON td.MACLB2 = clb2.MACLB
```
**Logic:** Bảng CAULACBO được quét hai lần (dưới hai alias khác nhau) để lấy tên CLB nhà và CLB khách.

#### JOIN nhiều bảng
```sql
SELECT HOTEN, TENCLB, TENQG
FROM (CAUTHU
      INNER JOIN QUOCGIA ON CAUTHU.MAQG = QUOCGIA.MAQG)
INNER JOIN CAULACBO ON CAUTHU.MACLB = CAULACBO.MACLB
```
**Logic:** JOIN được thực hiện từng bước: đầu tiên join CAUTHU với QUOCGIA, kết quả trung gian đó tiếp tục join với CAULACBO.

---

### 2.7 GROUP BY và Hàm Gộp

#### Hàm gộp (Aggregate Functions)
| Hàm | Chức năng | Ghi chú |
|-----|-----------|---------|
| `COUNT(*)` | Đếm tất cả dòng (kể cả NULL) | Không bỏ NULL |
| `COUNT(col)` | Đếm dòng không NULL | Bỏ qua NULL |
| `SUM(col)` | Tổng | Chỉ dùng với số |
| `AVG(col)` | Trung bình | Bỏ qua NULL |
| `MAX(col)` | Giá trị lớn nhất | |
| `MIN(col)` | Giá trị nhỏ nhất | |

```sql
-- Thống kê trên toàn bảng:
SELECT MIN(year(getdate()) - year(NGAYSINH)) AS MINAGE,
       MAX(year(getdate()) - year(NGAYSINH)) AS MAXAGE,
       AVG(year(getdate()) - year(NGAYSINH)) AS AVGAGE
FROM CAUTHU
```

#### GROUP BY – Nhóm dữ liệu
```sql
SELECT TENCLB, COUNT(MACT) AS [Số lượng cầu thủ]
FROM CAULACBO clb
JOIN CAUTHU ct ON clb.MACLB = ct.MACLB
GROUP BY TENCLB
```
**Quy tắc quan trọng:** Mọi cột trong SELECT mà **không phải hàm gộp** đều phải xuất hiện trong GROUP BY. Nếu không, SQL Server sẽ báo lỗi (vì nó không biết lấy giá trị nào cho cột đó trong nhóm có nhiều dòng).

#### HAVING – Lọc nhóm
```sql
SELECT TENCLB, COUNT(MACT) AS [Số lượng cầu thủ]
FROM CAULACBO clb
JOIN CAUTHU ct ON clb.MACLB = ct.MACLB
WHERE ct.MAQG <> 'VN'       -- lọc trước khi nhóm
GROUP BY TENCLB
HAVING COUNT(MACT) >= 2     -- lọc sau khi nhóm
```
**WHERE vs HAVING:**
- `WHERE` chạy **trước** GROUP BY → lọc từng dòng thô.
- `HAVING` chạy **sau** GROUP BY → lọc từng nhóm đã tính.
- Không được dùng hàm gộp trong WHERE.

---

### 2.8 Subquery – Truy Vấn Con

Truy vấn con là SELECT lồng bên trong một truy vấn khác.

#### So sánh với kết quả subquery (trả về 1 giá trị)
```sql
-- Tìm cầu thủ lớn tuổi nhất:
SELECT clb.TENCLB, ct.HOTEN,
       year(getdate()) - year(NGAYSINH) AS [Tuổi]
FROM CAULACBO clb
INNER JOIN CAUTHU ct ON clb.MACLB = ct.MACLB
WHERE year(getdate()) - year(NGAYSINH) =
      (SELECT MAX(year(getdate()) - year(NGAYSINH)) FROM CAUTHU)
```
**Logic:** Subquery chạy trước, tính ra tuổi lớn nhất (1 giá trị). Truy vấn ngoài dùng giá trị đó làm điều kiện lọc.

#### ANY / ALL
```sql
WHERE tuổi > ALL (SELECT tuổi FROM ...)   -- lớn hơn TẤT CẢ giá trị
WHERE tuổi > ANY (SELECT tuổi FROM ...)   -- lớn hơn ÍT NHẤT 1 giá trị
```

#### IN với subquery
```sql
-- Tìm CLB không tham gia trận đấu năm 2009:
SELECT TENCLB FROM CAULACBO
WHERE MACLB NOT IN (SELECT MACLB1 FROM TRANDAU WHERE nam = '2009')
  AND MACLB NOT IN (SELECT MACLB2 FROM TRANDAU WHERE nam = '2009')
```

#### EXISTS
```sql
WHERE EXISTS (SELECT 1 FROM TRANDAU WHERE ...)
```
**Logic của EXISTS:** Không quan tâm dữ liệu subquery trả về là gì — chỉ kiểm tra xem có **ít nhất 1 dòng** không. Dừng lại ngay khi tìm thấy dòng đầu tiên (hiệu quả hơn `IN` với bảng lớn).

---

### 2.9 INSERT – Thêm Dữ Liệu

```sql
-- Thêm 1 dòng với giá trị cụ thể:
INSERT INTO CAULACBO
VALUES ('SLNA', N'Sông Lam Nghệ An', 'CL', 'KH')

-- Thêm từ kết quả SELECT:
INSERT INTO newtable
SELECT * FROM CAULACBO
```
**Logic:** `VALUES` phải khớp số lượng và thứ tự cột. Nếu chỉ điền một số cột, phải liệt kê tên cột: `INSERT INTO t (col1, col2) VALUES (...)`.

---

### 2.10 UPDATE – Cập Nhật Dữ Liệu

```sql
UPDATE CAULACBO
   SET TENCLB = N'Đội tuyển SLNA'
 WHERE MACLB = 'SLNA'

-- UPDATE với CASE:
UPDATE CAUTHU
   SET DIACHI = CASE WHEN MACT < 3 THEN N'Hà Nội' ELSE N'Nghệ An' END
```
**Cảnh báo:** UPDATE không có WHERE sẽ cập nhật **toàn bộ bảng**. Luôn kiểm tra WHERE trước bằng SELECT.

---

### 2.11 DELETE – Xóa Dữ Liệu

```sql
DELETE FROM CAULACBO WHERE MACLB = 'SLNA'

-- Xóa toàn bộ (nhanh hơn DELETE):
TRUNCATE TABLE tên_bảng
```
**DELETE vs TRUNCATE:**
| | DELETE | TRUNCATE |
|-|--------|----------|
| WHERE | Có thể dùng | Không |
| Ghi log | Từng dòng | Chỉ ghi page |
| Tốc độ | Chậm hơn | Nhanh hơn |
| Kích hoạt TRIGGER | Có | Không |
| Reset IDENTITY | Không | Có |

---

## 3. DDL – Ngôn Ngữ Định Nghĩa Dữ Liệu

### 3.1 CREATE TABLE

```sql
CREATE TABLE CAUTHU (
    MACT     INT          IDENTITY(1,1) PRIMARY KEY,
    HOTEN    NVARCHAR(100) NOT NULL,
    VITRI    NVARCHAR(50)  NULL,
    NGAYSINH DATETIME      NULL,
    DIACHI   NVARCHAR(50)  NULL,
    MACLB    VARCHAR(5)    NOT NULL,
    MAQG     VARCHAR(5)    NOT NULL,
    SO       INT
)
```
- `IDENTITY(1,1)`: tự tăng, bắt đầu từ 1, bước nhảy 1.
- `NOT NULL`: bắt buộc nhập dữ liệu.
- Nên dùng `NVARCHAR` cho dữ liệu tiếng Việt (hỗ trợ Unicode).

### 3.2 Ràng Buộc (Constraints)

#### CHECK – Kiểm tra điều kiện hợp lệ
```sql
CREATE TABLE TRANDAU (
    MATRAN INT    IDENTITY(1,1) PRIMARY KEY,
    NAM    INT    NOT NULL,
    VONG   INT    NOT NULL CONSTRAINT chk_vong CHECK (VONG BETWEEN 0 AND 10),
    ...
)
```
**Logic:** Mỗi INSERT/UPDATE, SQL Server đánh giá điều kiện CHECK. Nếu sai → rollback dòng đó, báo lỗi.

#### PRIMARY KEY
```sql
-- Khóa chính đơn:
MACT INT IDENTITY(1,1) PRIMARY KEY

-- Khóa chính tổ hợp:
CONSTRAINT chk_primarykey PRIMARY KEY (MAHLV, MACLB)
```
Khóa chính đảm bảo: **duy nhất** + **không NULL**. Tự động tạo index clustered.

#### FOREIGN KEY
```sql
CONSTRAINT fk_maclb
FOREIGN KEY (MACLB) REFERENCES CAULACBO(MACLB)
ON DELETE CASCADE
ON UPDATE NO ACTION
```
**Logic tham chiếu:**
- `CASCADE`: xóa/sửa bảng cha → tự động xóa/sửa bảng con.
- `NO ACTION` (mặc định): từ chối xóa/sửa bảng cha nếu còn dòng con tham chiếu.
- `SET NULL`: đặt FK thành NULL khi bảng cha bị xóa.
- `SET DEFAULT`: đặt FK về giá trị mặc định.

---

### 3.3 ALTER TABLE

```sql
-- Thêm cột:
ALTER TABLE HLV_CLB ADD description NVARCHAR(100) NULL

-- Thay đổi kiểu cột:
ALTER TABLE HLV_CLB ALTER COLUMN description NVARCHAR(200) NULL

-- Thêm ràng buộc:
ALTER TABLE HLV_CLB
ADD CONSTRAINT chk_desc CHECK (LEN(description) > 10)

-- Xóa ràng buộc:
ALTER TABLE HLV_CLB DROP CONSTRAINT chk_desc

-- Xóa cột:
ALTER TABLE HLV_CLB DROP COLUMN description
```
**Lưu ý:** Không thể thêm cột NOT NULL vào bảng đã có dữ liệu trừ khi có DEFAULT. Muốn xóa cột đang bị FK tham chiếu → phải xóa FK trước.

---

### 3.4 DROP TABLE

```sql
DROP TABLE tên_bảng
```
**Không thể hoàn tác.** Xóa luôn toàn bộ dữ liệu, index, trigger, constraint. Không thể DROP nếu còn bảng khác có FK trỏ vào.

---

### 3.5 VIEW – Khung Nhìn

```sql
CREATE VIEW v_cauthu AS
SELECT MACT,
       HOTEN,
       year(getdate()) - year(NGAYSINH) AS TUOI,
       VITRI
FROM CAUTHU

-- Truy vấn view như bảng:
SELECT * FROM v_cauthu

-- Thay đổi view:
ALTER VIEW v_cauthu AS ...

-- Xóa view:
DROP VIEW v_cauthu
```
**View không lưu dữ liệu** — mỗi lần truy vấn, SQL Server chạy lại câu SELECT bên trong. View giúp:
- Che giấu độ phức tạp của JOIN.
- Giới hạn cột/dòng người dùng thấy (bảo mật).
- Tái sử dụng logic truy vấn.

**Khi nào view cho phép INSERT/UPDATE/DELETE?**
- SELECT không có DISTINCT, TOP, GROUP BY, UNION.
- Danh sách chọn chỉ là cột gốc, không có biểu thức tính toán.

---

## Tóm Tắt Thứ Tự Thực Thi SQL

```
FROM (& JOIN)   → xác định bảng nguồn, nhân tích đề-các
WHERE           → lọc từng dòng
GROUP BY        → gom nhóm
HAVING          → lọc nhóm
SELECT          → chọn cột, tính toán, alias
DISTINCT        → loại dòng trùng
ORDER BY        → sắp xếp
TOP / LIMIT     → cắt bớt kết quả
```

Hiểu thứ tự này giúp tránh lỗi "alias không nhận ra trong WHERE" hay "hàm gộp không được phép trong WHERE".
