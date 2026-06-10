@echo off
:: Chuyển mã sang UTF-8 để hiển thị tiếng Việt
chcp 65001 >nul

set INBOX_DIR=.\Inbox
set ARCHIVE_DIR=.\Inbox\Archive

:: Di chuyển vào Inbox
cd /d "%INBOX_DIR%" || (
    echo Khong tim thay thu muc Inbox!
    pause
    exit /b 1
)

:: Tự động tạo thư mục Archive nếu chưa có
if not exist "Archive" mkdir "Archive"

echo Bat dau cay PDF va tu dong don dep...

:: Tìm và lặp qua tất cả các file có đuôi .pdf
for %%f in (*.pdf) do (
    echo ------------------------------------------------
    echo [Folder] Dang ep: "%%f" -^> "%%~nf.md"
    
    :: Trích xuất text từ PDF ra Markdown
    markitdown "%%f" -o "%%~nf.md"
    
    :: Kiểm tra xem file .md đã được tạo thành công chưa
    if exist "%%~nf.md" (
        echo [OK] Da tao xong .md -^> Dang cat file PDF goc vao Archive...
        move "%%f" "Archive\" >nul
    ) else (
        echo [Loi] Khong the convert file "%%f"
    )
)

echo ------------------------------------------------
echo Xong xuoi! Toan bo file .md da san sang!
pause