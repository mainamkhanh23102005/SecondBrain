Hướng dẫn thực hành CSDL

BÀI THỰC HÀNH SỐ 3:

Thao tác dữ liệu với T-SQL nâng cao – Một số hàm quan trọng

Mục lục ...................................................................................................................................................................... 1

1

1.1

1.1.1

1.1.2

1.2

1.2.1

1.2.2

1.2.3

1.2.4

1.2.5

1.2.6

1.2.7

1.2.8

Các hàm quan trọng trong T-SQL ...................................................................................................... 2

Các hàm làm việc với kiểu dữ liệu số ..................................................................................... 2

Hàm ISNUMERIC ................................................................................................................. 2

Hàm ROUND .......................................................................................................................... 2

Các hàm làm việc với kiểu dữ liệu chuỗi............................................................................... 3

Hàm LEFT ................................................................................................................................. 3

Hàm RIGHT .............................................................................................................................. 3

Hàm SUBSTRING ................................................................................................................. 3

Hàm LEN ................................................................................................................................... 4

Hàm REPLACE...................................................................................................................... 4

Hàm STUFF .............................................................................................................................. 4

Hàm LOWER/UPPER .......................................................................................................... 5

Hàm LTRIM/RTRIM ............................................................................................................ 5

1.3

Các hàm làm việc với kiểu dữ liệu Ngày tháng/ Thời gian .......................................... 5

1.3.1

1.3.2

1.3.3

1.3.4

Hàm GETDATE ..................................................................................................................... 6

Hàm DAY/ MONTH/ YEAR ............................................................................................ 6

Hàm DATEPART.................................................................................................................. 6

Hàm DATENAME ................................................................................................................ 6

1.4

HàmCAST và CONVERTER ............................................................................................ 7

1

Hướng dẫn thực hành CSDL

1.  Các hàm quan trọng trong T-SQL

Ngôn ngữ T-SQL có nhiều hàm có thể tham gia vào câu lệnh T-SQL. Những hàm này thực hiện
các nhiệm vụ quan trọng khác nhau. Trong chương này sẽ trình bày một số các hàm thông dụng
để  làm  việc  với  các  kiểu  dữ  liệu  số,  chuỗi,  ngày/thời  gian  và  giá  trị  NULL  trong  SQL  Server
2005.

1.1 Các hàm làm việc với kiểu dữ liệu số
Các hàm quan trọng làm việc với kiểu dữ liệu số là hàm ISNUMERIC và ham ROUND

1.1.1 Hàm ISNUMERIC
Hàm isNumeric kiểm tra một giá trị có phải thuộc kiểu dữ liệu số hay không.

Ví dụ: Câu lệnh dưới đây trả về tên khách hàng, và một cột có tên NUMERIC. Cột này sẽ

mang giá trị 0 nếu địa chỉ khách hàng không phải là số và ngược lại

select HOTEN, isnumeric(MACT) as ISNUMERIC from CAUTHU

1.1.2 Hàm ROUND
Hàm ROUND trả về một giá trị số, đã được làm tròn theo một độ đài chỉ định

Cấu trúc hàm ROUND như sau:

ROUND ( số_làm_tròn , độ_dài_làm_tròn )

Khi sử dụng hàm ROUND cần lưu ý:

số_làm_tròn phải có kiểu dữ liệu số (numeric data type) như int, float, decimal… trừ kiểu dữ liệu
dạng nhị phân. Cho dù số_làm_tròn thuộc kiểu dữ liệu gì, kết quả hàm ROUND luôn trả về kiều
số nguyên.
Nếu độ_dài_làm_tròn là số âm và lớn hơn số chữ số phía trước dấu thập phân thì hàm

ROUND trả về 0.

Ví dụ :

2

Hướng dẫn thực hành CSDL

select ROUND(123.9994, 3), ROUND(123.9995, 3)

Ví dụ 2:

select ROUND(123.4545, 2),ROUND(123.45, -2)

Ví dụ 3:

SELECT ROUND(150.75, 0), ROUND(150.75, 0, 1)

1.2 Các hàm làm việc với kiểu dữ liệu chuỗi

Các hàm quan trọng bao gồm LEFT, RIGHT, LEN, REPLACE, STUFF, SUBSTRING, LOWER,
UPPER, LTRIM, and RTRIM.

1.2.1 Hàm LEFT

Hàm LEFT trả về một chuỗi ký tự có chiều dài được chỉ định tính từ bên trái của chuỗi.

Ví dụ:

select left('Nha Trang', 5)

1.2.2 Hàm RIGHT

Hàm RIGHT tương tự hàm LEFT nhưng tính từ bên phải của chuỗi

Ví dụ:

select right('Nha Trang', 5)

1.2.3 Hàm SUBSTRING

Hàm STRING trích xuất một chuỗi con từ một chuỗi cho trước.

Cấu trúc hàm SUBSTRING như sau:

SUBSTRING (chuỗi_ban_đầu, vị_trí_bắt_đầu, chiều_dài_chuỗi_con)

Ví dụ 1:

3

Hướng dẫn thực hành CSDL

select substring ('Nha Trang', 2, 5)

Ví dụ 2:

Select substring('Nha Trang', -2, 5)

1.2.4 Hàm LEN

Hàm LEN trả về chiều dài một chuỗi

Ví dụ:

Select len('Nha Trang')

1.2.5 Hàm REPLACE

Hàm REPLACE thay thế một chuỗi bởi một chuỗi khác

Ví dụ 1: Câu lệnh dưới đây thay thế chữ “Nha” trong chuỗi Nha Trang bằng chữ “nha”

Select replace('Nha Trang', 'Nha', 'nha')

Ví dụ 2:
select replace(VITRI, N'Tiền', N'tiền')

from CAUTHU

1.2.6 Hàm STUFF

Hàm STUFF thay thế một số lượng xác định các ký tự trong một chuỗi bằng một chuỗi

khác bắt đầu từ một vị trí được chỉ định.

Ví dụ:

select stuff('Nha Trang', 2, 3, '***')

4

Hướng dẫn thực hành CSDL

1.2.7 Hàm LOWER/UPPER
Hàm LOWER chuyển các ký tự hoa trong chuỗi thành các kí tự thường. Hàm UPPER

chuyển các chuỗi ký tự thường trong chuỗi thành các ký tự hoa. Ví dụ:

select lower('Nha Trang'), upper('Nha Trang')

1.2.8 Hàm LTRIM/RTRIM

Hàm LTRIM cắt các khoảng trắng bên trái của chuỗi, hàm RTRIM cắt khoảng trắng bên phải
chuỗi.
Ví dụ:
declare @llen int declare @rlen int declare @len
int select @llen = len(ltrim(' Nha Trang')),
@rlen = len(rtrim('Nha Trang  ')),
@len = len('Nha Trang')

select @llen, @rlen, @len

1.3 Các hàm làm việc với kiểu dữ liệu Ngày tháng/ Thời gian

1.3.1 Hàm GETDATE
Hàm GETDATE trả về ngày giờ lúc thực hiện câu truy vấn.

Ví dụ:
select getdate()

1.3.2 Hàm DAY/ MONTH/ YEAR
Hàm DAY trả về ngày của một một giá trị thuộc kiểu datetime. Hàm MONTH trả về tháng của
một giá trị thuộc kiểu datetime
Hàm YEAR trả về năm của một giá trị thuộc kiểu datetime.

Ví dụ:
select HOTEN,VITRI,day (NGAYSINH) as [Ngày sinh], month(NGAYSINH) as [Tháng
sinh], year(NGAYSINH) as [Năm sinh]
from CAUTHU where MACT = 5

5

Hướng dẫn thực hành CSDL

1.3.3 Hàm DATEPART

Trong quá trình làm  việc với các CSDL, đôi  lúc ta  muốn biết xem  một ngày  nào  đó thuộc quý
mấy trong năm, hay thuộc tuần thứ mấy trong tháng. Hàm DATEPART giúp giải quyết các yêu
cầu trên một cách dễ dàng.
Cấu trúc hàm DATEPART như sau:

DATEPART (yêu_cầu_trích_xuất, giá_trị_trích_xuất)

giá_trị_trích_xuất là một giá trị thuộc kiểu datetime.

yêu_cầu_trích_xuất: ngày, tháng, năm, quý,….
Khi có một yêu cầu trích xuất nào đó, chúng ta sẽ có các chữ viết tắt tương ứng với các

yêu cầu đó. Bảng dưới đây mô tả các yêu chữ viết tắt và các yêu cầu trích xuất tương ứng.

Ý nghĩa

Năm

Quý

Tháng

Số ngày đã qua trong năm

Ngày

Tuần

Số ngày đã qua trong tuần

Giờ

Phút

Giây

Chữ viết tắt

yy, yyyy

qq,q

mm,m

dy,y

dd,d

wk,ww

dw

hh

mi,n

ss,s

Ví dụ:
select datepart(yyyy, NGAYSINH)as NAMSINH, datepart(qq, NGAYSINH)as QUYSINH,

datepart(m, NGAYSINH) as THANGSINH, datepart(wk, NGAYSINH) as TUANSINH, datepart(d,
NGAYSINH) as NGAYSINH, datepart(dy, NGAYSINH), datepart(dw, NGAYSINH) from CAUTHU
where MACT = 5

1.3.4 Hàm DATENAME

Tương tự hàm DATEPART nhưng hàm DATENAME trả về một chuỗi ký tự

Ví dụ:
select datename(yyyy, NGAYSINH)as NAMSINH, datename(qq, NGAYSINH)as QUYSINH,

6

Hướng dẫn thực hành CSDL

datename(m, NGAYSINH) as THANGSINH, datename(wk, NGAYSINH) as TUANSINH, datename(d,

NGAYSINH) as NGAYSINH, datename(dy, NGAYSINH), datename(dw, NGAYSINH) from CAUTHU

where MACT = 5

1.4 Hàm CAST và CONVERTER

Chuyển  đổi  một  giá  trị  thuộc  kiểu  dữ  liệu  này  sang  một  kiểu  dữ  liệu  khác.  Hàm  CAST  và
CONVERTER cung cấp cùng một chức năng. Một điểm thuận lợi khi dùng CONVERTER là khi
chuyển đổi, hàm này cũng cho phép người dùng sẽ định dạng lại giá tri kết quả theo ý muốn.

Cấu trúc hàm CAST và CONVERTER như sau:

CAST (biểu_thức/giá_ trị AS kiểu_dữ liệu [độ_dài_kiểu_dữ_liệu ])

CONVERT ( kiểu_dữ liệu [độ_dài_kiểu_dữ_liệu ] , biểu_thức/giá_ trị [ ,kiểu_định_dạng] )

Năm 2 chữ số

Năm 4 chữ số

Output

0 hoặc 100

mon dd yyyy hh:mi AM (PM)

1

2

3

4

5

6

7

8

10

11

12

14

101

102

103

104

105

106

107

108

mm/dd/yy

yy.mm.dd

dd/mm/yy

dd.mm.yy

dd-mm-yy

dd mon yy

Mon dd, yy

hh:mm:ss

9 hoặc 109

mon dd yyyy hh:mi:ss:mmmAM (PM)

110

111

112

mm-dd-yy

yy/mm/dd

yymmdd

13 hoặc 113

dd mon yyyy hh:mm:ss:mmm(24h)

114

hh:mi:ss:mmm(24h)

Ví dụ:
Select HOTEN, convert (varchar, NGAYSINH, 103) as NGAYSINH,

VITRI from CAUTHU

where year(getdate()) - year(NGAYSINH) > 20

7

Hướng dẫn thực hành CSDL

Hàm CONVERT và hàm CAST có thể sử dụng kết hợp với nhau để cho kết qua như

mong muốn.

8

Hướng dẫn thực hành CSDL

9

