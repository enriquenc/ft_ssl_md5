echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > big_smoke_order_remix
./ft_ssl sha256 -q big_smoke_order_remix
openssl sha256 big_smoke_order_remix
echo "23a0944d11b5a54f1970492b5265c732044ae824b7d5656acb193e7f0e51e5fa"
./ft_ssl sha256 -s "wubba lubba dub dub"
