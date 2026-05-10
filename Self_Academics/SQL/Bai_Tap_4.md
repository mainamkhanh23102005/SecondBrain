# Bài Tập 4 – Trigger và Stored Procedure

**Nguồn:** Bài tập thực hành CSDL – IT3090 – Bài Thực Hành 4
**Tags:** #sql #t-sql #stored-procedure #trigger #database #qlbongda

---

## Nền Tảng Lý Thuyết

### Stored Procedure là gì?

Stored Procedure (SP) là một khối lệnh T-SQL được đặt tên, lưu trữ trên server, và có thể gọi tái sử dụng nhiều lần. SP có thể nhận tham số đầu vào (INPUT) và trả về tham số đầu ra (OUTPUT).

```sql
-- Tạo SP:
CREATE PROCEDURE tên_sp
    @tham_so_vao   kiểu_dữ_liệu,
    @tham_so_ra    kiểu_dữ_liệu OUTPUT
AS
BEGIN
    -- Thân procedure
END

-- Gọi SP:
EXEC tên_sp @gt1, @gt2 OUTPUT
```

**Lợi ích của Stored Procedure:**
- Tái sử dụng, giảm lặp code.
- Bảo mật: người dùng chỉ cần quyền EXEC SP, không cần quyền trực tiếp trên bảng.
- Giảm lưu lượng mạng: gửi tên SP thay vì toàn bộ câu SQL.
- Kế hoạch thực thi (execution plan) được cache lại.

---

### Trigger là gì?

Trigger là một loại Stored Procedure đặc biệt, **tự động chạy** khi có sự kiện INSERT / UPDATE / DELETE xảy ra trên bảng.

```sql
CREATE TRIGGER tên_trigger
ON tên_bảng
AFTER INSERT | UPDATE | DELETE   -- hoặc INSTEAD OF
AS
BEGIN
    -- Thân trigger
END
```

**Hai bảng ảo trong Trigger:**
| Bảng | Có trong | Chứa dữ liệu |
|------|----------|-------------|
| `INSERTED` | INSERT, UPDATE | Dòng **mới** (sau thay đổi) |
| `DELETED` | DELETE, UPDATE | Dòng **cũ** (trước thay đổi) |

Khi UPDATE: `DELETED` = giá trị cũ, `INSERTED` = giá trị mới.

**AFTER vs INSTEAD OF:**
- `AFTER`: chạy **sau** khi thao tác hoàn thành. Có thể rollback nếu vi phạm.
- `INSTEAD OF`: chạy **thay thế** thao tác gốc. Dùng nhiều trên VIEW.

---

## Phần A – Bài Tập Stored Procedure

### Bài 1: In ra 'Xin chào'

```sql
CREATE PROCEDURE sp_XinChao
AS
BEGIN
    PRINT N'Xin chào'
END

-- Thực thi:
EXEC sp_XinChao
```

**Logic:** `PRINT` gửi thông điệp văn bản về Messages tab. Không trả về result set.

---

### Bài 2: In ra 'Xin chào' + tên người dùng (tham số INPUT)

```sql
CREATE PROCEDURE sp_XinChaoTen
    @ten NVARCHAR(100)
AS
BEGIN
    PRINT N'Xin chào ' + @ten
END

-- Thực thi:
EXEC sp_XinChaoTen @ten = N'Minh'
-- Hoặc: EXEC sp_XinChaoTen N'Minh'
```

**Logic:** Tham số `@ten` là INPUT (mặc định). Ghép chuỗi bằng `+`. Dùng `N''` cho Unicode tiếng Việt.

---

### Bài 3: Nhập 2 số, in ra tổng

```sql
CREATE PROCEDURE sp_Tong
    @s1 INT,
    @s2 INT
AS
BEGIN
    DECLARE @tg INT
    SET @tg = @s1 + @s2
    PRINT N'Tổng là: ' + CAST(@tg AS NVARCHAR)
END

-- Thực thi:
EXEC sp_Tong @s1 = 10, @s2 = 25
```

**Logic:** `DECLARE` khai báo biến cục bộ. `CAST(@tg AS NVARCHAR)` chuyển số sang chuỗi để ghép với `PRINT`. Không dùng `+` giữa INT và NVARCHAR trực tiếp — SQL Server sẽ báo lỗi kiểu dữ liệu.

---

### Bài 4a: In số lớn nhất của 2 số

```sql
CREATE PROCEDURE sp_SoLonNhat
    @s1 INT,
    @s2 INT
AS
BEGIN
    DECLARE @max INT
    IF @s1 >= @s2
        SET @max = @s1
    ELSE
        SET @max = @s2

    PRINT N'Số lớn nhất của ' + CAST(@s1 AS NVARCHAR)
        + N' và ' + CAST(@s2 AS NVARCHAR)
        + N' là ' + CAST(@max AS NVARCHAR)
END

EXEC sp_SoLonNhat 15, 8
```

**Logic:** Cấu trúc `IF...ELSE` trong T-SQL. Không có `elif` — nếu cần nhiều nhánh dùng `IF...ELSE IF...ELSE` hoặc `CASE`.

---

### Bài 4b: Xuất tổng ra tham số OUTPUT

```sql
CREATE PROCEDURE sp_TongOutput
    @s1   INT,
    @s2   INT,
    @tong INT OUTPUT
AS
BEGIN
    SET @tong = @s1 + @s2
END

-- Thực thi và kiểm tra:
DECLARE @ketqua INT
EXEC sp_TongOutput @s1 = 10, @s2 = 20, @tong = @ketqua OUTPUT
PRINT N'Tổng = ' + CAST(@ketqua AS NVARCHAR)
```

**Logic của OUTPUT parameter:** Tham số được đánh dấu `OUTPUT` trong cả định nghĩa SP và lúc gọi. Biến `@ketqua` sẽ nhận giá trị sau khi SP chạy xong.

---

### Bài 5: Xuất min và max ra OUTPUT

```sql
CREATE PROCEDURE sp_MinMax
    @s1  INT,
    @s2  INT,
    @min INT OUTPUT,
    @max INT OUTPUT
AS
BEGIN
    IF @s1 <= @s2
    BEGIN
        SET @min = @s1
        SET @max = @s2
    END
    ELSE
    BEGIN
        SET @min = @s2
        SET @max = @s1
    END
END

-- Thực thi:
DECLARE @minVal INT, @maxVal INT
EXEC sp_MinMax 30, 10, @minVal OUTPUT, @maxVal OUTPUT
PRINT N'Min = ' + CAST(@minVal AS NVARCHAR) + N', Max = ' + CAST(@maxVal AS NVARCHAR)
```

**Logic:** Khi IF có nhiều lệnh, bắt buộc dùng `BEGIN...END` để nhóm lại.

---

### Bài 6: In các số từ 1 đến N

```sql
CREATE PROCEDURE sp_DemDenN
    @n INT
AS
BEGIN
    DECLARE @i INT = 1
    WHILE @i <= @n
    BEGIN
        PRINT CAST(@i AS NVARCHAR)
        SET @i = @i + 1
    END
END

EXEC sp_DemDenN 10
```

**Logic của WHILE:** `WHILE điều_kiện BEGIN ... END`. T-SQL không có `FOR` loop — dùng WHILE thay thế. Nhớ tăng biến đếm `@i` hoặc sẽ lặp vô hạn.

---

### Bài 7: Tổng các số chẵn từ 1 đến N

```sql
CREATE PROCEDURE sp_TongChan
    @n INT
AS
BEGIN
    DECLARE @i   INT = 1
    DECLARE @sum INT = 0
    WHILE @i <= @n
    BEGIN
        IF @i % 2 = 0          -- kiểm tra số chẵn (chia 2 dư 0)
            SET @sum = @sum + @i
        SET @i = @i + 1
    END
    PRINT N'Tổng các số chẵn từ 1 đến ' + CAST(@n AS NVARCHAR)
        + N' = ' + CAST(@sum AS NVARCHAR)
END

EXEC sp_TongChan 10   -- Kết quả: 2+4+6+8+10 = 30
```

**Logic:** Toán tử `%` là modulo (chia lấy dư). `@i % 2 = 0` → số chẵn.

---

### Bài 8: Tổng VÀ số lượng các số chẵn từ 1 đến N (OUTPUT)

```sql
CREATE PROCEDURE sp_TongSoLuongChan
    @n        INT,
    @tong     INT OUTPUT,
    @soluong  INT OUTPUT
AS
BEGIN
    DECLARE @i INT = 1
    SET @tong    = 0
    SET @soluong = 0
    WHILE @i <= @n
    BEGIN
        IF @i % 2 = 0
        BEGIN
            SET @tong    = @tong + @i
            SET @soluong = @soluong + 1
        END
        SET @i = @i + 1
    END
END

-- Thực thi và kiểm tra:
DECLARE @t INT, @sl INT
EXEC sp_TongSoLuongChan 10, @t OUTPUT, @sl OUTPUT
PRINT N'Tổng = ' + CAST(@t AS NVARCHAR) + N', Số lượng = ' + CAST(@sl AS NVARCHAR)
```

---

### Bài 9: SP tương ứng các câu View

Mỗi câu query đã dùng trong View, viết thành SP để nhận tham số linh hoạt hơn.

```sql
-- Ví dụ: View lấy danh sách cầu thủ theo CLB → SP nhận @maclb:
CREATE PROCEDURE sp_CauThuTheoCLB
    @maclb VARCHAR(5)
AS
BEGIN
    SELECT ct.HOTEN, ct.VITRI, clb.TENCLB
    FROM CAUTHU ct
    INNER JOIN CAULACBO clb ON ct.MACLB = clb.MACLB
    WHERE ct.MACLB = @maclb
END

EXEC sp_CauThuTheoCLB 'HAN'
```

---

### Bài 10: CRUD Stored Procedures cho từng bảng

Mỗi bảng cần 4 SP: **Select / Insert / Update / Delete**. Ví dụ cho bảng `CAUTHU`:

```sql
-- SELECT:
CREATE PROCEDURE sp_CAUTHU_Select
    @mact INT = NULL    -- NULL = lấy tất cả
AS
BEGIN
    SELECT * FROM CAUTHU
    WHERE (@mact IS NULL OR MACT = @mact)
END

-- INSERT:
CREATE PROCEDURE sp_CAUTHU_Insert
    @hoten    NVARCHAR(100),
    @vitri    NVARCHAR(50),
    @ngaysinh DATETIME,
    @diachi   NVARCHAR(200),
    @maclb    VARCHAR(5),
    @maqg     VARCHAR(5),
    @so       INT
AS
BEGIN
    INSERT INTO CAUTHU (HOTEN, VITRI, NGAYSINH, DIACHI, MACLB, MAQG, SO)
    VALUES (@hoten, @vitri, @ngaysinh, @diachi, @maclb, @maqg, @so)
END

-- UPDATE (khóa chính MACT làm tham số):
CREATE PROCEDURE sp_CAUTHU_Update
    @mact     INT,
    @hoten    NVARCHAR(100),
    @vitri    NVARCHAR(50),
    @ngaysinh DATETIME,
    @diachi   NVARCHAR(200),
    @maclb    VARCHAR(5),
    @maqg     VARCHAR(5),
    @so       INT
AS
BEGIN
    UPDATE CAUTHU
       SET HOTEN    = @hoten,
           VITRI    = @vitri,
           NGAYSINH = @ngaysinh,
           DIACHI   = @diachi,
           MACLB    = @maclb,
           MAQG     = @maqg,
           SO       = @so
     WHERE MACT = @mact
END

-- DELETE (khóa chính MACT làm tham số):
CREATE PROCEDURE sp_CAUTHU_Delete
    @mact INT
AS
BEGIN
    DELETE FROM CAUTHU WHERE MACT = @mact
END
```

**Logic thiết kế CRUD SP:**
- SELECT: nhận PK tùy chọn (NULL = lấy tất cả).
- INSERT: nhận tất cả cột (trừ IDENTITY).
- UPDATE/DELETE: **bắt buộc có PK** để xác định dòng cần thao tác.

---

## Phần B – Bài Tập Trigger

### Bài 1: Kiểm tra vị trí cầu thủ hợp lệ

```sql
CREATE TRIGGER trg_KiemTraViTri
ON CAUTHU
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM INSERTED
        WHERE VITRI NOT IN (N'Thủ môn', N'Tiền đạo', N'Tiền vệ', N'Trung vệ', N'Hậu vệ')
    )
    BEGIN
        ROLLBACK TRANSACTION
        RAISERROR(N'Vị trí cầu thủ không hợp lệ!', 16, 1)
    END
END
```

**Logic:** Bảng `INSERTED` chứa dòng mới vừa INSERT. Trigger kiểm tra nếu có dòng nào có VITRI không trong danh sách cho phép → `ROLLBACK` hủy toàn bộ transaction INSERT đó. `RAISERROR` trả về thông báo lỗi cho client.

---

### Bài 2: Kiểm tra số áo không trùng trong cùng CLB

```sql
CREATE TRIGGER trg_KiemTraSoAo
ON CAUTHU
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED i
        INNER JOIN CAUTHU ct ON i.MACLB = ct.MACLB
                            AND i.SO    = ct.SO
                            AND i.MACT <> ct.MACT   -- không so sánh với chính nó
    )
    BEGIN
        ROLLBACK TRANSACTION
        RAISERROR(N'Số áo đã tồn tại trong câu lạc bộ này!', 16, 1)
    END
END
```

**Logic:** JOIN bảng `INSERTED` với `CAUTHU` để tìm cầu thủ khác cùng CLB đã có số áo đó. Điều kiện `i.MACT <> ct.MACT` loại bỏ việc dòng mới so sánh với chính nó (vì sau INSERT, dòng mới đã có trong CAUTHU).

---

### Bài 3: Thông báo khi thêm cầu thủ mới

```sql
CREATE TRIGGER trg_ThongBaoThemCauThu
ON CAUTHU
AFTER INSERT
AS
BEGIN
    PRINT N'Đã thêm cầu thủ mới'
END
```

**Logic:** Trigger đơn giản nhất — chỉ in thông báo, không kiểm tra gì. Trigger `AFTER INSERT` luôn chạy sau khi INSERT thành công.

---

### Bài 4: Giới hạn tối đa 8 cầu thủ nước ngoài mỗi CLB

```sql
CREATE TRIGGER trg_GioiHanCauThuNuocNgoai
ON CAUTHU
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT i.MACLB
        FROM INSERTED i
        WHERE i.MAQG <> 'VN'    -- cầu thủ nước ngoài vừa thêm
        GROUP BY i.MACLB
        HAVING (
            SELECT COUNT(*)
            FROM CAUTHU ct
            WHERE ct.MACLB = i.MACLB
              AND ct.MAQG <> 'VN'
        ) > 8
    )
    BEGIN
        ROLLBACK TRANSACTION
        RAISERROR(N'CLB đã đủ 8 cầu thủ nước ngoài!', 16, 1)
    END
END
```

**Logic:** Sau khi INSERT, đếm tổng số cầu thủ nước ngoài của CLB trong bảng CAUTHU. Nếu > 8 → rollback.

---

### Bài 5: Tên quốc gia không được trùng

```sql
CREATE TRIGGER trg_TenQuocGiaKhongTrung
ON QUOCGIA
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED i
        INNER JOIN QUOCGIA qg ON i.TENQG = qg.TENQG
                             AND i.MAQG <> qg.MAQG
    )
    BEGIN
        ROLLBACK TRANSACTION
        RAISERROR(N'Tên quốc gia đã tồn tại!', 16, 1)
    END
END
```

---

### Bài 6: Tên tỉnh thành không được trùng

```sql
CREATE TRIGGER trg_TenTinhThanhKhongTrung
ON TINHthanh
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED i
        INNER JOIN TINHthanh tt ON i.TENTINH = tt.TENTINH
                               AND i.MATINH  <> tt.MATINH
    )
    BEGIN
        ROLLBACK TRANSACTION
        RAISERROR(N'Tên tỉnh thành đã tồn tại!', 16, 1)
    END
END
```

---

### Bài 7: Không cho sửa kết quả trận đã diễn ra

```sql
CREATE TRIGGER trg_KhoaSuaKetQua
ON TRANDAU
AFTER UPDATE
AS
BEGIN
    IF UPDATE(KETQUA)   -- kiểm tra cột KETQUA có bị thay đổi không
    BEGIN
        IF EXISTS (
            SELECT 1 FROM DELETED
            WHERE NGAYTD < GETDATE()   -- trận đã qua
        )
        BEGIN
            ROLLBACK TRANSACTION
            RAISERROR(N'Không thể sửa kết quả trận đã diễn ra!', 16, 1)
        END
    END
END
```

**Logic:** Trong trigger UPDATE, `DELETED` chứa dữ liệu cũ. `UPDATE(KETQUA)` trả về TRUE nếu câu UPDATE đụng vào cột KETQUA. So sánh `NGAYTD < GETDATE()` xác định trận đã diễn ra.

---

### Bài 8: Kiểm tra vai trò HLV khi phân công

```sql
-- 8a: Kiểm tra vai trò hợp lệ
CREATE TRIGGER trg_KiemTraVaiTroHLV
ON HLV_CLB
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM INSERTED
        WHERE VAITRO NOT IN (N'HLV chính', N'HLV phụ', N'HLV thể lực', N'HLV thủ môn')
    )
    BEGIN
        ROLLBACK TRANSACTION
        RAISERROR(N'Vai trò HLV không hợp lệ!', 16, 1)
    END
END

-- 8b: Mỗi CLB tối đa 2 HLV chính
CREATE TRIGGER trg_GioiHanHLVChinh
ON HLV_CLB
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT i.MACLB
        FROM INSERTED i
        WHERE i.VAITRO = N'HLV chính'
        GROUP BY i.MACLB
        HAVING (
            SELECT COUNT(*) FROM HLV_CLB h
            WHERE h.MACLB = i.MACLB AND h.VAITRO = N'HLV chính'
        ) > 2
    )
    BEGIN
        ROLLBACK TRANSACTION
        RAISERROR(N'Mỗi CLB chỉ có tối đa 2 HLV chính!', 16, 1)
    END
END
```

---

### Bài 9: Kiểm tra CLB trùng tên

```sql
-- 9c: Chỉ thông báo, vẫn cho INSERT:
CREATE TRIGGER trg_ThongBaoCLBTrungTen
ON CAULACBO
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED i
        INNER JOIN CAULACBO clb ON i.TENCLB = clb.TENCLB
                               AND i.MACLB <> clb.MACLB
    )
        PRINT N'Cảnh báo: Đã có câu lạc bộ trùng tên!'
    -- Không ROLLBACK → INSERT vẫn thành công
END

-- 9d: Thông báo VÀ không cho INSERT:
CREATE TRIGGER trg_ChặnCLBTrungTen
ON CAULACBO
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED i
        INNER JOIN CAULACBO clb ON i.TENCLB = clb.TENCLB
                               AND i.MACLB <> clb.MACLB
    )
    BEGIN
        ROLLBACK TRANSACTION
        RAISERROR(N'Câu lạc bộ trùng tên đã tồn tại!', 16, 1)
    END
END
```

---

### Bài 10: Khi sửa tên cầu thủ — báo cáo các trường hợp

```sql
-- 10e: Chỉ in mã cầu thủ vừa sửa:
CREATE TRIGGER trg_SuaTenCauThu_e
ON CAUTHU
AFTER UPDATE
AS
BEGIN
    IF UPDATE(HOTEN)
        SELECT MACT AS [Mã cầu thủ vừa sửa] FROM INSERTED
END

-- 10f: In mã + tên mới:
CREATE TRIGGER trg_SuaTenCauThu_f
ON CAUTHU
AFTER UPDATE
AS
BEGIN
    IF UPDATE(HOTEN)
        SELECT MACT, HOTEN AS [Tên mới] FROM INSERTED
END

-- 10g: In mã + tên cũ:
CREATE TRIGGER trg_SuaTenCauThu_g
ON CAUTHU
AFTER UPDATE
AS
BEGIN
    IF UPDATE(HOTEN)
        SELECT MACT, HOTEN AS [Tên cũ] FROM DELETED
END

-- 10h: In mã + tên cũ + tên mới:
CREATE TRIGGER trg_SuaTenCauThu_h
ON CAUTHU
AFTER UPDATE
AS
BEGIN
    IF UPDATE(HOTEN)
        SELECT i.MACT,
               d.HOTEN AS [Tên cũ],
               i.HOTEN AS [Tên mới]
        FROM INSERTED i
        JOIN DELETED d ON i.MACT = d.MACT
END

-- 10i: In thông báo tiếng Việt với mã cầu thủ:
CREATE TRIGGER trg_SuaTenCauThu_i
ON CAUTHU
AFTER UPDATE
AS
BEGIN
    IF UPDATE(HOTEN)
    BEGIN
        DECLARE @mact INT
        SELECT @mact = MACT FROM INSERTED   -- nếu UPDATE nhiều dòng, chỉ lấy 1
        PRINT N'Vừa sửa thông tin của cầu thủ có mã số ' + CAST(@mact AS NVARCHAR)
    END
END
```

**Logic quan trọng cho 10i:** Khi UPDATE nhiều dòng cùng lúc, `INSERTED` có nhiều dòng, nhưng `SELECT @mact = MACT FROM INSERTED` chỉ lấy 1 giá trị tùy ý. Để xử lý đúng nhiều dòng, cần dùng CURSOR hoặc in từng dòng qua SELECT + `PRINT` kết hợp với `STRING_AGG`/subquery.

---

## Tóm Tắt

| Loại | Khi nào dùng | Kích hoạt |
|------|-------------|-----------|
| Stored Procedure | Logic tái sử dụng, tham số hóa truy vấn | Gọi thủ công với EXEC |
| Trigger AFTER | Kiểm tra/log sau khi thao tác | Tự động khi INSERT/UPDATE/DELETE |
| Trigger INSTEAD OF | Thay thế hoàn toàn thao tác | Tự động, thường dùng với VIEW |

**Lưu ý chung khi viết Trigger:**
1. Trigger xử lý **tập hợp dòng**, không phải từng dòng — luôn JOIN với `INSERTED`/`DELETED`, không dùng `SELECT TOP 1` giả định.
2. `ROLLBACK` trong trigger hủy toàn bộ transaction gốc.
3. Trigger lồng nhau (nested trigger) có thể xảy ra nếu trigger gọi SP có INSERT/UPDATE/DELETE khác — cẩn thận vòng lặp vô hạn.
