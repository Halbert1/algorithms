ʹ��nodejs�https
https://www.jianshu.com/p/6406584ef018

linux����֤��
1,����˽Կ
#openssl genrsa -out private.pem 1024
˵����
1. genrsa --- ʹ��RSA�㷨����˽Կ
3. -out   --- ����ļ���·��
4. 1024   --- ָ��˽Կ����

2,����˽Կ����csr֤��ǩ��
#openssl req -new -key private.pem -out csr.pem  -subj "/C=CN/ST=myprovince/L=mycity/O=myorganization/OU=mygroup/CN=myname"
˵����
1. req -- ִ��֤��ǩ������
2. -new -- ��֤��ǩ������
3. -key -- ָ��˽Կ·��
4. -out -- �����csr�ļ���·��
5. -subj -- ֤����ص��û���Ϣ(subject����д)

3, ��ǩ��֤��
# openssl x509 -req -days 365 -sha1 -extensions v3_ca -signkey  private.pem -in csr.pem -out ca.cer
˵����
1. x509  -- ����x509��ʽ֤��
2. -req -- ����csr�ļ�
3. -days -- ֤�����Ч�ڣ��죩
4. -sha1 -- ֤��ժҪ����sha1�㷨
5. -extensions  -- ����openssl.cnf�ļ������õ�v3_ca�������չ
6. -signkey  -- ǩ��֤���˽Կ
7. -in  -- Ҫ�����csr�ļ�
8. -out -- �����cer֤���ļ�


ca_dir·���µ��ļ�:
#openssl genrsa -out privatekey.pem 1024
#openssl req -new -key privatekey.pem -out certrequest.csr 
#openssl x509 -req -in certrequest.csr -signkey privatekey.pem -out certificate.pem
