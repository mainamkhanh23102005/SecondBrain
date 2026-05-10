> [!info] Metadata
> 
> **Source:** Video YouTube "ML Zoomcamp 1.1 - Introduction to Machine Learning" (DataTalksClub)
> 
> **Document Type:** Type A (Theoretical/Conceptual)

### 1. Tổng quan Tài liệu (Executive Summary)

Tài liệu này là bài giảng nhập môn cơ bản nhất về **Machine Learning (ML)**. Thông qua một bài toán thực tế là dự đoán giá xe hơi cũ trên một trang web rao vặt, giảng viên giải thích bản chất cốt lõi của ML: Làm thế nào để tự động hóa việc đưa ra quyết định hoặc dự đoán dựa trên dữ liệu lịch sử, thay vì phải dựa vào trực giác hoặc phân tích thủ công của chuyên gia.

### 2. Trích xuất Trọng tâm (Zero-Loss Extraction)

**A. Các thuật ngữ nền tảng (Core Concepts)**

Dưới góc nhìn của hệ thống Machine Learning, dữ liệu được chia thành các thành phần sau:

- **Features (Đặc trưng):** Là toàn bộ những thông tin, thuộc tính mà chúng ta biết về một đối tượng (Object). Ví dụ với xe hơi: `age` (tuổi đời), `manufacturer` (nhà sản xuất), `mileage` (số km đã đi), `model`, v.v.
    
- **Target (Biến mục tiêu):** Là giá trị mà chúng ta muốn hệ thống dự đoán ra. Trong bài toán này, nó chính là `price` (giá xe).
    
- **Model (Mô hình):** Một "chiếc hộp đen" chứa đựng toàn bộ các quy luật, khuôn mẫu (patterns) đã được hệ thống học từ dữ liệu trong quá khứ.
    
- **Predictions (Dự đoán):** Đầu ra cuối cùng của Model khi được nạp **Features** của một đối tượng mới hoàn toàn.
    

**B. Luồng hoạt động của hệ thống ML (System Flow)**

- **Giai đoạn Huấn luyện (Training Phase):** `Features` + `Target` $\rightarrow$ **Machine Learning Algorithm** $\rightarrow$ `Model`
    
- **Giai đoạn Dự đoán (Inference/Prediction Phase):** `Features` (Của xe mới, không có Target) $\rightarrow$ `Model` $\rightarrow$ `Predictions`
    

### 3. Giải thích Cặn kẽ (Deep-Dive Explanations)

**Vấn đề (The Problem): Tại sao lại cần ML ở đây?**

Khi người dùng đăng bán xe cũ, việc chọn mức giá rất nhạy cảm. Giá quá cao (`too high`) thì không ai mua, giá quá thấp (`too low`) thì mất tiền (leaving money on the table). Thông thường, một chuyên gia (expert) có thể nhìn vào tình trạng xe và đoán giá vì họ đã có kinh nghiệm nhìn thấy hàng ngàn chiếc xe tương tự được bán ra.

**Giải pháp (The ML Solution): Đóng gói kinh nghiệm của chuyên gia**

Thay vì thuê chuyên gia định giá từng chiếc xe, ML bắt chước chính cách mà bộ não chuyên gia hoạt động: **Học từ dữ liệu quá khứ**.

- **Step-by-step logic:** Chúng ta gom tất cả dữ liệu lịch sử của các xe đã bán thành một bảng (Table). Các cột thông tin kỹ thuật làm `Features`, cột giá bán làm `Target`. Thuật toán ML sẽ quét qua toàn bộ dữ liệu này để tự động tìm ra mối liên hệ (Ví dụ: xe BMW thì đắt hơn Volkswagen, xe số km đi càng nhiều thì giá càng giảm). Nó "đóng gói" (encapsulate) tất cả các quy luật này lại thành một `Model`.
    
- **Ứng dụng thực tế:** Khi người dùng điền thông tin lên form bán xe (`Features`), hệ thống ngầm đẩy thông tin đó qua `Model`, và tự động suggest một mức giá hợp lý (`Predictions`) để người dùng tham khảo.
    

> [!warning] Chú ý: Điểm giới hạn của Model (Pitfall)
> 
> Model **không** bao giờ dự đoán chính xác 100% từng đồng cho một chiếc xe cụ thể (có thể cao hơn hoặc thấp hơn thực tế). Tuy nhiên, về mặt bản chất, các dự đoán của nó được thiết kế để mang tính **chính xác trên mức trung bình (correct on average)** so với toàn bộ thị trường.

### 4. Tổng hợp & Mở rộng (Key Takeaways & Next Steps)

**💡 3 Điểm Cốt Lõi Cần Nhớ:**

1. Bản chất của Machine Learning là quá trình **trích xuất tự động các khuôn mẫu (extracting patterns) từ dữ liệu**, mô phỏng lại cách con người rút ra kinh nghiệm.
    
2. Để training, bạn bắt buộc phải cung cấp cả **Features** lẫn **Target**.
    
3. Để prediction, bạn chỉ cần cung cấp **Features** để lấy ra kết quả.
    

**🚀 Tư duy Mở rộng (Complex Discussion):**

1. **Câu hỏi tư duy 1:** Trong video, hệ thống học từ những xe đã có sẵn giá bán (có Target). Đây gọi là _Supervised Learning_ (Học có giám sát). Vậy nếu ta có một tập dữ liệu xe hơi nhưng **không hề có giá bán**, ML có thể giúp chúng ta làm được gì với tập dữ liệu đó?
    
2. **Next Step:** Nội dung tiếp theo của khóa học sẽ là so sánh sự khác biệt giữa Machine Learning model (tự học luật từ data) và Rule-based systems (lập trình viên tự viết các luật `if/else` cứng dể định giá/phân loại). Thử tưởng tượng, nếu dùng Rule-based system để định giá xe, hệ thống mã code của bạn sẽ trông hỗn loạn như thế nào?