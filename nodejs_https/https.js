//ʹ��nodejs�Դ���http��httpsģ��
var https = require('https');
var http = require('http');
var fs = require('fs');

 
var options = {
    key: fs.readFileSync('./ca_dir/privatekey.pem'),
    cert: fs.readFileSync('./ca_dir/certificate.pem')
};


//����http��HTTPS������
var httpServer = http.createServer(function(req, res){
    res.end('This is http visit!');
    console.log('HTTP Server is running on:');
}).listen(9001);

var httpsServer = https.createServer(options, function(req, res){
    res.end('This is https visit!');
    console.log('HTTsssssssssssssss');
}).listen(9000);
