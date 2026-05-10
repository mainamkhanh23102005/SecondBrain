# Thực Hành SQL - Bài 4: Stored Procedure, Trigger, Cursor, Function

> **Nguồn:** Hướng Dẫn Thực Hành CSDL - Bài Số 4
> **Chủ đề:** Procedure, Trigger, Cursor, Function trong T-SQL (SQL Server)

---

## Tổng quan

Bài này tập trung vào bốn công cụ lập trình phía server của SQL Server. Tất cả đều cho phép đóng gói logic nghiệp vụ ngay trong database — thay vì để logic đó nằm tản mát ở tầng ứng dụng.

| Công cụ | Kích hoạt | Trả về | Dùng khi |
|---|---|---|---|
| Stored Procedure | Gọi thủ công bằng `EXEC` | Tùy ý (hoặc không) | Logic phức tạp, batch operation |
| Trigger | Tự động khi INSERT/UPDATE/DELETE | Không trả về trực tiếp | Enforce rules, audit, cascade |
| Cursor | Duyệt từng hàng từ SELECT | Biến T-SQL | Cần xử lý row-by-row |
| Function | Gọi trong biểu thức SQL | Scalar hoặc Table | Tính toán tái sử dụng trong query |

---

## 1. Stored Procedure

### 1.1 Khái niệm & Lý do dùng

**Stored Procedure (SP)** là một khối T-SQL được đặt tên, biên dịch sẵn và lưu trong database. Khi gọi lại, SQL Server **không cần parse lại** — nó dùng execution plan đã được cache → nhanh hơn.

**Bốn lợi ích chính:**
1. **Tái sử dụng** — viết một lần, gọi nhiều lần từ nhiều nơi.
2. **Hiệu năng** — execution plan được cache sau lần chạy đầu.
3. **Giảm traffic mạng** — thay vì gửi 100 câu SQL lên server, chỉ gửi 1 lệnh `EXEC`.
4. **Bảo mật** — có thể cấp quyền `EXEC` mà không cấp quyền trực tiếp trên bảng.

### 1.2 Cú pháp cốt lõi

```sql
-- Tạo
CREATE PROCEDURE procedure_name
    @param1 data_type,
    @param2 data_type OUTPUT   -- tham số đầu ra
AS
BEGIN
    -- logic T-SQL
END

-- Gọi
EXEC procedure_name value1, value2

-- Sửa (giữ nguyên permission)
ALTER PROCEDURE procedure_name ...

-- Xóa
DROP PROCEDURE procedure_name
```

> **Lưu ý:** `CREATE PROC` là viết tắt hợp lệ của `CREATE PROCEDURE`.
> Tên biến và hàm **không phân biệt hoa thường** trong SQL Server.

---

### 1.3 Phân tích ví dụ chi tiết

#### Ví dụ 1 — SP tính tổng 2 số (có tham số OUTPUT)

```sql
CREATE PROCEDURE sp_Tong
    @So1  INT,
    @So2  INT,
    @Tong INT OUTPUT     -- <-- OUTPUT: giá trị ghi ngược ra ngoài
AS
BEGIN
    SET @Tong = @So1 + @So2;
END
```

**Logic:**
- `@So1`, `@So2` là tham số đầu vào (IN) — người gọi truyền giá trị vào.
- `@Tong OUTPUT` là tham số đầu ra (OUT) — SP ghi kết quả vào đây, người gọi đọc lại.
- Bên trong SP: `SET @Tong = @So1 + @So2` — phép cộng đơn giản, lưu vào biến OUTPUT.

**Gọi thực thi:**
```sql
DECLARE @Sum INT               -- khai báo biến để nhận kết quả
EXEC sp_Tong 1, -2, @Sum OUT  -- gọi SP, truyền 1 và -2, nhận kết quả vào @Sum
SELECT @Sum                    -- in kết quả: -1
```

**Luồng dữ liệu:**
```
Caller          →    SP
1, -2           →    @So1=1, @So2=-2
                ←    @Tong=-1  (ghi ngược qua OUTPUT)
@Sum = -1       ←
```

---

#### Ví dụ 2 — SP không tham số, trả về tập kết quả

```sql
CREATE PROCEDURE sp_Thongtincaulacbo
AS
BEGIN
    SELECT TENCLB, COUNT(MACT) AS SOLUONGCT
    FROM CAUTHU ct, CAULACBO clb
    WHERE ct.MACLB = clb.MACLB
    GROUP BY TENCLB
END
```

**Logic:**
- SP này **không có tham số** → luôn trả về toàn bộ dữ liệu.
- `JOIN` ngầm: `CAUTHU ct, CAULACBO clb WHERE ct.MACLB = clb.MACLB` — đây là cú pháp JOIN kiểu cũ (ANSI-89), tương đương `CAUTHU INNER JOIN CAULACBO ON ct.MACLB = clb.MACLB`.
- `COUNT(MACT)` đếm số cầu thủ trong mỗi câu lạc bộ.
- `GROUP BY TENCLB` nhóm kết quả theo tên CLB — bắt buộc phải có khi dùng `COUNT`.

**Kết quả trả về:** Một bảng gồm tên CLB và số cầu thủ tương ứng.

---

#### Ví dụ 3 — SP phức tạp với nhiều OUTPUT và xử lý lỗi

```sql
CREATE PROC dbo.ThemHuanLuyenVien
    @MAHLV      VARCHAR(5)    = NULL,
    @TENHLV     NVARCHAR(100) = NULL,
    @NGAYSINH   DATETIME      = NULL,
    @DIACHI     NVARCHAR(100) = NULL,
    @DIENTHOAI  NVARCHAR(20)  = NULL,
    @MAQG       VARCHAR(5)    = NULL,
    @identity   INT           OUTPUT,
    @returnMessage NVARCHAR(50) OUTPUT
AS
SET NOCOUNT ON

SET @identity = 0;
SET @ReturnMessage = '';

IF @MAHLV IS NULL
    SET @returnMessage = 'So hieu HLV trong';
ELSE
BEGIN
    DECLARE @error INT, @id INT

    INSERT INTO dbo.HUANLUYENVIEN
    VALUES (@MAHLV, @TENHLV, @NGAYSINH, @DIACHI, @DIENTHOAI, @MAQG);

    SELECT @error = @@ERROR,
           @id    = SCOPE_IDENTITY();

    IF @error = 0
    BEGIN
        SET @identity = @id;
        SET @ReturnMessage = 'Complete';
    END
    ELSE
        SET @ReturnMessage = 'Error';
END
```

**Phân tích từng phần:**

| Phần | Giải thích |
|---|---|
| `= NULL` sau mỗi tham số | **Giá trị mặc định** — cho phép gọi SP mà bỏ qua tham số |
| `SET NOCOUNT ON` | Tắt thông báo "N rows affected" → giảm traffic |
| `IF @MAHLV IS NULL` | Validate input — nếu mã HLV rỗng thì không INSERT |
| `INSERT INTO dbo.HUANLUYENVIEN VALUES (...)` | Thêm bản ghi HLV mới vào bảng |
| `@@ERROR` | Biến hệ thống: `0` = thành công, khác `0` = có lỗi |
| `SCOPE_IDENTITY()` | Lấy giá trị IDENTITY (auto-increment) vừa được INSERT → trả về cho caller |
| `@identity OUTPUT` | Caller nhận được ID của bản ghi vừa tạo |
| `@returnMessage OUTPUT` | Caller nhận được thông điệp trạng thái: `'Complete'` hoặc `'Error'` |

**Luồng thực thi:**
```
Gọi SP
  ↓
@MAHLV IS NULL?
  ├── Có → set message = 'So hieu HLV trong', kết thúc
  └── Không → INSERT vào bảng
              ↓
           @@ERROR = 0?
              ├── Có → @identity = SCOPE_IDENTITY(), message = 'Complete'
              └── Không → message = 'Error'
```

---

## 2. Trigger

### 2.1 Khái niệm

**Trigger** là SP đặc biệt — **tự động kích hoạt** khi có sự kiện DML (INSERT/UPDATE/DELETE) xảy ra trên một bảng cụ thể. Người dùng không gọi trigger trực tiếp. 

**Đặc điểm quan trọng nhất — hai bảng ảo:**

| Bảng ảo | Tồn tại khi | Chứa gì |
|---|---|---|
| `inserted` | INSERT, UPDATE | Các hàng **mới** (vừa được thêm/sửa) |
| `deleted` | DELETE, UPDATE | Các hàng **cũ** (vừa bị xóa/bị ghi đè) |

> Với UPDATE: hàng cũ → `deleted`, hàng mới → `inserted`. Hai bảng cùng tồn tại.

### 2.2 Cú pháp

```sql
-- Tạo
CREATE TRIGGER trigger_name ON table_name
FOR [INSERT, UPDATE, DELETE]
AS
BEGIN
    -- logic T-SQL, có thể đọc inserted/deleted
END

-- Xóa
DROP TRIGGER trigger_name
```

### 2.3 Phân tích ví dụ — Trigger xử lý xóa phiếu mượn

```sql
CREATE TRIGGER tg_delMuon ON muon
FOR DELETE
AS
BEGIN
    DECLARE @isbn INT, @ma_cuonsach SMALLINT

    SELECT @isbn = isbn, @ma_cuonsach = ma_cuonsach
    FROM deleted                        -- đọc hàng vừa bị xóa

    UPDATE cuonsach
    SET tinhtrang = 'yes'
    WHERE isbn = @isbn AND ma_cuonsach = @ma_cuonsach
END
```

**Logic:**
1. Khi một hàng bị `DELETE` khỏi bảng `muon` (phiếu mượn sách), trigger tự kích hoạt.
2. Hàng vừa xóa được lưu tạm trong bảng ảo `deleted`.
3. Trigger đọc `isbn` và `ma_cuonsach` từ `deleted` → biết cuốn sách nào vừa được trả.
4. Trigger cập nhật bảng `cuonsach`: đặt `tinhtrang = 'yes'` (cuốn sách có sẵn trở lại).

**Ý nghĩa nghiệp vụ:** Khi xóa phiếu mượn = người dùng trả sách → hệ thống tự động đánh dấu sách có sẵn. Đây là **cascade logic** — một hành động kéo theo hành động khác tự động.

> **Cảnh báo:** Trigger này chỉ xử lý đúng khi mỗi lệnh `DELETE` xóa **đúng 1 hàng**. Nếu `DELETE` nhiều hàng cùng lúc, `deleted` chứa nhiều hàng nhưng `@isbn` chỉ nhận 1 giá trị → bug. Cần dùng Cursor hoặc JOIN để xử lý đúng.

---

## 3. Cursor

### 3.1 Khái niệm

**Cursor** là con trỏ trỏ vào tập kết quả của một câu `SELECT`. Nó cho phép xử lý **từng hàng một** (row-by-row) thay vì toàn bộ tập dữ liệu cùng lúc.

> **Quan trọng:** SQL hoạt động tốt nhất theo kiểu set-based (xử lý tập hợp). Cursor là giải pháp cuối cùng khi logic thực sự cần duyệt từng hàng. Cursor thường chậm hơn JOIN/subquery nhiều.

### 3.2 Vòng đời của Cursor

```
DECLARE → OPEN → FETCH (loop) → CLOSE → DEALLOCATE
```

| Bước | Lệnh | Tác dụng |
|---|---|---|
| Khai báo | `DECLARE cursor_name CURSOR FOR SELECT ...` | Định nghĩa tập dữ liệu |
| Mở | `OPEN cursor_name` | Thực thi SELECT, cursor trỏ trước hàng đầu |
| Lấy dữ liệu | `FETCH NEXT FROM cursor INTO @var1, @var2` | Di chuyển con trỏ xuống 1 hàng, đọc vào biến |
| Kiểm tra | `@@FETCH_STATUS = 0` | `0` = còn hàng, `< 0` = hết hàng |
| Đóng | `CLOSE cursor_name` | Giải phóng tập kết quả |
| Hủy | `DEALLOCATE cursor_name` | Giải phóng cấu trúc cursor khỏi bộ nhớ |

### 3.3 Phân tích ví dụ 1 — Duyệt đơn giản

```sql
DECLARE @btt INT, @btt2 INT
DECLARE @c CURSOR

SET @c = CURSOR FOR
    SELECT tt, tt2 FROM bang1 WHERE [điều kiện]

OPEN @c
FETCH NEXT FROM @c INTO @btt, @btt2  -- lần fetch đầu tiên (seed)

WHILE @@FETCH_STATUS = 0
BEGIN
    -- xử lý @btt, @btt2 ở đây
    FETCH NEXT FROM @c INTO @btt, @btt2  -- tiến đến hàng tiếp theo
END

CLOSE @c
DEALLOCATE @c
```

**Điểm quan trọng — "seed fetch":**
- `FETCH NEXT` đầu tiên **trước vòng lặp** là bắt buộc — nó nạp hàng đầu tiên và set `@@FETCH_STATUS`.
- Nếu bỏ qua bước này, `@@FETCH_STATUS` chưa được khởi tạo và vòng lặp có thể chạy sai.
- `FETCH NEXT` cuối vòng lặp — chuẩn bị hàng tiếp theo cho lần lặp sau.

---

### 3.4 Phân tích ví dụ 2 — Cursor lồng nhau

```sql
DECLARE @c CURSOR
SET @c = CURSOR FOR SELECT TOP 2 ma_docgia FROM DocGia
OPEN @c

DECLARE @madg VARCHAR(66)
FETCH NEXT FROM @c INTO @madg

WHILE @@FETCH_STATUS = 0
BEGIN
    PRINT @madg

    -- Cursor lồng bên trong
    DECLARE @c2 CURSOR
    SET @c2 = CURSOR FOR SELECT TOP 4 ma_tuaSach FROM TuaSach
    OPEN @c2

    DECLARE @mats VARCHAR(66)
    FETCH NEXT FROM @c2 INTO @mats

    WHILE @@FETCH_STATUS = 0
    BEGIN
        PRINT ' ' + @mats
        FETCH NEXT FROM @c2 INTO @mats
    END

    CLOSE @c2
    DEALLOCATE @c2
    -- PHẢI deallocate @c2 trước khi declare lại ở vòng lặp tiếp theo

    FETCH NEXT FROM @c INTO @madg
END

CLOSE @c
DEALLOCATE @c
```

**Logic:**
- Vòng ngoài duyệt 2 độc giả đầu tiên.
- Với mỗi độc giả, vòng trong duyệt 4 tựa sách đầu tiên và in ra.
- `@@FETCH_STATUS` dùng chung cho cả hai cursor → khi cursor trong đang chạy, `@@FETCH_STATUS` phản ánh trạng thái của **cursor trong**. Sau khi cursor trong kết thúc và bị DEALLOCATE, `FETCH NEXT FROM @c` tiếp theo sẽ reset lại `@@FETCH_STATUS` cho cursor ngoài.
- **Bắt buộc `DEALLOCATE @c2` trong mỗi vòng lặp** — nếu không, lần lặp sau khi `DECLARE @c2` lại sẽ báo lỗi "cursor already exists".

---

## 4. Function (Hàm)

### 4.1 Khái niệm

**Function** khác với Stored Procedure ở chỗ:
- Function **trả về giá trị** và có thể dùng **trong biểu thức SQL** (`SELECT`, `WHERE`, `JOIN`).
- SP thì không thể nhúng trực tiếp vào câu SELECT.

Hai loại Function trong SQL Server:

| Loại | `RETURNS` | Gọi như |
|---|---|---|
| Scalar Function | `INT`, `VARCHAR`, ... | `dbo.tenHam(args)` — dùng được trong `SELECT`, `WHERE` |
| Inline Table-Valued | `TABLE` | `tenHam(args)` — dùng như một bảng trong `FROM` |

### 4.2 Cú pháp

```sql
CREATE FUNCTION function_name
    ( [@param data_type] )
RETURNS [return_data_type]   -- 'RETURNS' có 's', khác 'RETURN'
AS
BEGIN
    RETURN [scalar_value hoặc SELECT]
END
```

### 4.3 Phân tích ví dụ 1 — Scalar Function tính tuổi

```sql
-- Xóa nếu đã tồn tại (pattern an toàn trước khi tạo lại)
IF OBJECT_ID('fTuoi', 'FN') IS NOT NULL
    DROP FUNCTION fTuoi
GO

CREATE FUNCTION fTuoi (@ns INT)
RETURNS INT
AS
BEGIN
    RETURN YEAR(GETDATE()) - @ns
END
GO

-- Kiểm tra
PRINT dbo.fTuoi(1982)   -- In ra tuổi của người sinh năm 1982
```

**Logic:**
- `OBJECT_ID('fTuoi', 'FN')` — kiểm tra xem hàm scalar `fTuoi` đã tồn tại chưa. `'FN'` = Scalar Function.
- `GETDATE()` trả về ngày giờ hiện tại.
- `YEAR(GETDATE())` lấy năm hiện tại.
- `RETURN YEAR(GETDATE()) - @ns` — tính tuổi đơn giản bằng cách lấy năm hiện tại trừ năm sinh.
- **Lưu ý:** Khi gọi Scalar Function phải có prefix `dbo.` → `dbo.fTuoi(1982)`.

---

### 4.4 Phân tích ví dụ 2 — Inline Table-Valued Function

```sql
-- Xóa nếu đã tồn tại ('IF' = Inline Table-Valued Function)
IF OBJECT_ID('fDSach', 'IF') IS NOT NULL
    DROP FUNCTION fDSach
GO

-- Bảng T có cột: namsinh INT
CREATE FUNCTION fDSach (@ns INT)
RETURNS TABLE
AS
    RETURN (SELECT * FROM T WHERE namsinh = @ns)
GO

-- Kiểm tra
SELECT * FROM fDSach(1982)   -- Không cần dbo. prefix
```

**Logic:**
- `RETURNS TABLE` (không phải `RETURNS INT`) — hàm trả về một tập hợp hàng như một bảng.
- Thân hàm chỉ có một câu `RETURN (SELECT ...)` — không có `BEGIN...END`.
- Hàm lọc bảng `T` theo năm sinh `@ns` và trả về toàn bộ các cột.
- Gọi bằng cách đặt trong mệnh đề `FROM` như một bảng: `FROM fDSach(1982)`.
- **Lưu ý:** Table-Valued Function **không cần `dbo.` prefix** khi gọi (khác Scalar Function).

**So sánh cách gọi:**
```sql
-- Scalar Function: cần dbo.
PRINT dbo.fTuoi(1982)
SELECT dbo.fTuoi(namsinh) FROM NhanVien

-- Table-Valued Function: dùng trong FROM, không cần dbo.
SELECT * FROM fDSach(1982)
SELECT t.*, f.col FROM SomeTable t CROSS APPLY fDSach(t.namsinh) f
```

---

## 5. So sánh nhanh & Khi nào dùng gì

```
Cần tự động phản ứng khi data thay đổi?
    → TRIGGER

Cần tính toán 1 giá trị để dùng trong câu SELECT/WHERE?
    → SCALAR FUNCTION

Cần lấy một tập kết quả dạng bảng để JOIN/FROM?
    → TABLE-VALUED FUNCTION

Cần thực hiện logic phức tạp, nhiều bước, INSERT/UPDATE/DELETE?
    → STORED PROCEDURE

Cần xử lý từng hàng một (logic row-by-row không thể viết set-based)?
    → CURSOR (dùng trong SP hoặc trigger)
```

---

## 6. Bài tập thực hành

Theo tài liệu gốc: làm các bài tập về Stored Procedure, Cursor, Trigger trong file `Baitapthuchanh.pdf`.

**Gợi ý khi làm bài:**
- Luôn test SP/Function sau khi tạo với `EXEC` / `SELECT dbo.ham()`.
- Dùng `@@ERROR` sau mỗi lệnh DML quan trọng để bắt lỗi.
- Với Trigger: dùng `ROLLBACK TRANSACTION` bên trong nếu muốn hủy thao tác gây ra trigger.
- Với Cursor: luôn nhớ `CLOSE` và `DEALLOCATE`, không bao giờ bỏ sót.

---

*Processed from: `Inbox/HuongDanTucHanh_V_P_F.md`*
Nhớ học nhé đồ dốt