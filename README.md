# Simple Local Chat (C Socket Programming)

Bu proje, C dilinde ağ programlamanın (Socket Programming) temellerini kavramak ve işletim sistemi seviyesinde süreç yönetimini (`fork()`) öğrenmek amacıyla geliştirilmiş asenkron bir Terminal sohbet uygulamasıdır. 

"My Engineering Vault" not sistemimin uygulamalı bir parçasıdır.

## 🚀 Özellikler

* **TCP Protokolü:** Veri kayıpsız, garantili ve sıralı iletişim altyapısı (Connection-oriented).
* **Asenkron İletişim (Full-Duplex):** `fork()` sistem çağrısı kullanılarak program okuma ve yazma işlemleri için iki ayrı sürece (process) bölünmüştür. Bu sayede taraflar mesaj beklerken aynı anda mesaj gönderebilir; sistem "bloklanmaz".
* **Geriye Dönük Uyumluluk (UDP):** Projenin ilk aşamasında yazılan, garantisiz ama hızlı `UDP` (sendto/recvfrom) iskeleti referans amacıyla klasörde tutulmaktadır.

## 🛠️ Kullanılan Teknolojiler ve Konseptler

* **Dil:** C
* **Kütüphaneler:** `<sys/socket.h>`, `<arpa/inet.h>`, `<unistd.h>`
* **Konseptler:** POSIX Sockets, Endianness (htons), Process Forking, Blocking/Non-blocking I/O.

## ⚙️ Nasıl Derlenir ve Çalıştırılır?

Bu projeyi yerel ortamda (localhost) test etmek için iki farklı terminal sekmesine ihtiyacınız vardır.

**1. Sunucuyu (Server) Derleme ve Çalıştırma:**
```bash
gcc tcp_server.c -o tcp_server
./tcp_server

**2. İstemciyi (Client) Derleme ve Çalıştırma:**

gcc tcp_client.c -o tcp_client
./tcp_client

🧠 My Engineering Vault - Temel Çıkarımlar

    htons() Neden Gereklidir? Bilgisayarlar (Little-Endian) ile Ağların (Big-Endian/Network Byte Order) sayıları okuma yönü farklıdır. Port numaralarını ağa verirken aradaki çeviriyi sağlamak zorunludur.

    Accept() Mekanizması: TCP sunucusu, kapıyı çalan her istemci için accept() ile yepyeni ve özel bir dosya tanımlayıcı (file descriptor) oluşturur. Ana soket dinlemeye devam eder.

    Sıralı vs. Asenkron: fgets ve recv işlemleri doğası gereği "blocking" (durdurucu) çağrılardır. Gerçek bir chat deneyimi için programı fork() ile iki ayrı iş parçacığına bölmek şarttır.
