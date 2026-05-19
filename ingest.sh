#!/bin/bash

# Đường dẫn tương đối trỏ vào thư mục Inbox
INBOX_DIR="./Inbox"
ARCHIVE_DIR="./Inbox/Archive"

# Di chuyển vào Inbox
cd "$INBOX_DIR" || { echo "Không tìm thấy thư mục Inbox!"; exit 1; }

# Tự động tạo thư mục Archive nếu chưa có
if [ ! -d "Archive" ]; then
    mkdir -p "Archive"
fi

echo "Bắt đầu cày PDF và tự động dọn dẹp..."

# Tìm và lặp qua tất cả các file có đuôi .pdf
for pdf_file in *.pdf; do
    # Kiểm tra xem có file pdf nào thật không
    if [ -f "$pdf_file" ]; then
        base_name="${pdf_file%.pdf}"
        
        echo "------------------------------------------------"
        echo "📂 Đang ép: $pdf_file -> $base_name.md"
        
        # 1. Trích xuất text từ PDF ra Markdown
        pdftotext -layout "$pdf_file" "$base_name.md"
        
        # 2. Kiểm tra xem file .md đã được tạo thành công chưa rồi mới ném file gốc vào Archive
        if [ -f "$base_name.md" ]; then
            echo "📦 Đã tạo xong .md -> Đang cất file PDF gốc vào Archive..."
            mv "$pdf_file" "Archive/"
        else
            echo "❌ Lỗi: Không thể convert file $pdf_file"
        fi
    fi
done

echo "------------------------------------------------"
echo "🎉 Xong xuôi! Toàn bộ file .md đã sẵn sàng, file PDF gốc đã được cất gọn vào Archive!"
