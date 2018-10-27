# Lossless Data Transfer

## Deskripsi Singkat

Komunikasi antar komputer merupakan hal yang sangat penting di abad 21 ini. Hampir semua aplikasi yang kita gunakan sehari-hari merupakan aplikasi yang berkomunikasi dengan komputer lain. Akan tetapi, komunikasi antar dua komputer tidak selalu berjalan sesuai yang diinginkan. Komunikasi antar komputer melalui jaringan rentan mengalami gangguan sehingga pesan yang dikirim tidak selalu bebas dari error. Untuk itu, perlu dilakukan deteksi terhadap error pada pesan untuk menjamin tingkat kebenaran pesan.

Untuk mendeteksi error, pihak penerima pesan akan melakukan pemeriksaan checksum pada setiap paket yang diterima. Jika terdapat error, maka penerima pesan akan meminta pengirim untuk mengirim ulang paket tersebut. Akan tetapi, jika hal ini dilakukan secara serial (hanya mengirim dan memeriksa satu paket pada satu waktu) akan menimbulkan masalah kinerja.

Solusi untuk permasalahan ini adalah dengan mengirim lebih dari satu paket dalam satu waktu. Solusi ini telah lama dikenal dalam dunia jaringan komputer dengan nama Sliding Window Protocol. Tujuan dari tugas besar ini adalah mempelajari cara kerja Sliding Window Protocol dengan Selective Repeat Automatic Repeat Request.