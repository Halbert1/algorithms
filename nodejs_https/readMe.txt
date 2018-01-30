使用nodejs搭建https
https://www.jianshu.com/p/6406584ef018

linux生成证书
1,生成私钥
#openssl genrsa -out private.pem 1024
说明：
1. genrsa --- 使用RSA算法产生私钥
3. -out   --- 输出文件的路径
4. 1024   --- 指定私钥长度

2,利用私钥生成csr证书签名
#openssl req -new -key private.pem -out csr.pem  -subj "/C=CN/ST=myprovince/L=mycity/O=myorganization/OU=mygroup/CN=myname"
说明：
1. req -- 执行证书签发命令
2. -new -- 新证书签发请求
3. -key -- 指定私钥路径
4. -out -- 输出的csr文件的路径
5. -subj -- 证书相关的用户信息(subject的缩写)

3, 自签发证书
# openssl x509 -req -days 365 -sha1 -extensions v3_ca -signkey  private.pem -in csr.pem -out ca.cer
说明：
1. x509  -- 生成x509格式证书
2. -req -- 输入csr文件
3. -days -- 证书的有效期（天）
4. -sha1 -- 证书摘要采用sha1算法
5. -extensions  -- 按照openssl.cnf文件中配置的v3_ca项添加扩展
6. -signkey  -- 签发证书的私钥
7. -in  -- 要输入的csr文件
8. -out -- 输出的cer证书文件


ca_dir路径下的文件:
#openssl genrsa -out privatekey.pem 1024
#openssl req -new -key privatekey.pem -out certrequest.csr 
#openssl x509 -req -in certrequest.csr -signkey privatekey.pem -out certificate.pem
