# fp-sisop-I07-2021

Made by:

Group I07

Gede Yoga Arisudana (05111942000009)

Salma Rahma Lailia (05111942000016)

Zulfiqar Rahman Aji (05111942000019)

## Final Project

Autentikasi
Ada username dan password tertentu untuk bisa akses database yang dia punya hak. Jika root (sudo) bisa akses semua database (tidak perlu didefinisikan secara rinci haknya, hanya dia bisa akses atau nggak).

### Format
```
./[program_client_database] -u [username] -p [password]
```

### Contoh
```
./client_databaseku -u jack -p jack123
```

Username, password, dan hak akses db disimpan di suatu database juga, tapi tidak ada user yang bisa akses database tersebut kecuali mengakses menggunakan root.
User root sudah ada dari awal.

### Contoh cara user root mengakses program client
```
sudo ./client_database
```
 
Menambahkan user (Hanya bisa dilakukan user root)

### Format
```
CREATE USER [nama_user] IDENTIFIED BY [password_user];
```

### Contoh
```
CREATE USER jack IDENTIFIED BY jack123;
```

Authorisasi
Untuk dapat mengakses database yang dia punya permission dengan command. Pembuatan tabel dan semua DML butuh untuk mengakses database terlebih dahulu.

### Format
```
USE [nama_database];
```

### Contoh
```
USE database1;
```

Yang bisa memberikan permission atas database untuk suatu user hanya root.

### Format
```
GRANT PERMISSION [nama_database] INTO [nama_user];
```

### Contoh
```
GRANT PERMISSION database1 INTO user1;
```

User hanya bisa mengakses database dimana dia diberi permission untuk database tersebut.
Data Definition Language
Input penamaan database, tabel, dan kolom hanya angka dan huruf.
Semua user bisa membuat database, otomatis user tersebut memiliki permission untuk database tersebut.

### Format
```
CREATE DATABASE [nama_database];
```

### Contoh
```
CREATE DATABASE database1;
```

Root dan user yang memiliki permission untuk suatu database untuk bisa membuat tabel untuk database tersebut, tentunya setelah mengakses database tersebut. Tipe data dari semua kolom adalah string atau integer. Jumlah kolom bebas.

### Format
```
CREATE TABLE [nama_tabel] ([nama_kolom] [tipe_data], ...);
```

### Contoh
```
CREATE TABLE table1 (kolom1 string, kolom2 int, kolom3 string, kolom4 int);
```
 
Bisa melakukan DROP database, table (setelah mengakses database), dan kolom. Jika sasaran drop ada maka didrop, jika tidak ada maka biarkan.

### Format
```
DROP [DATABASE | TABLE | COLUMN] [nama_database | nama_tabel | [nama_kolom] FROM [nama_tabel]];
```

### Contoh

#### Drop database
```
DROP DATABASE database1;
```

#### Drop table
```
DROP TABLE table1;
```

#### Drop Column
```
DROP COLUMN kolom1 FROM table1;
```

Data Manipulation Language
INSERT
Hanya bisa insert satu row per satu command. Insert sesuai dengan jumlah dan urutan kolom.

### Format
```
INSERT INTO [nama_tabel] ([value], ...);
```

### Contoh
```
INSERT INTO table1 (‘value1’, 2, ‘value3’, 4);
```

UPDATE
Hanya bisa update satu kolom per satu command.

### Format
```
UPDATE [nama_tabel] SET [nama_kolom]=[value];
```

### Contoh
```
UPDATE table1 SET kolom1=’new_value1’;
```

DELETE
Delete data yang ada di tabel.


### Format
```
DELETE FROM [nama_tabel];
```

### Contoh
```
DELETE FROM table1;
```

SELECT
### Format
```
SELECT [nama_kolom, … | *] FROM [nama_tabel];
```

### Contoh 1
```
SELECT kolom1, kolom2 FROM table1;
```

### Contoh 2
```
SELECT * FROM table1;
WHERE
Command UPDATE, SELECT, dan DELETE bisa dikombinasikan dengan WHERE. WHERE hanya untuk satu kondisi. Dan hanya ‘=’.
```

### Format
```
[Command UPDATE, SELECT, DELETE] WHERE [nama_kolom]=[value];
```

### Contoh
```
DELETE FROM table1 WHERE kolom1=’value1’;
```
Logging
Setiap command yang dipakai harus dilakukan logging ke suatu file dengan format. Jika yang eksekusi root, maka username root.

### Format di dalam log
```
timestamp(yyyy-mm-dd hh:mm:ss):username:command
```

### Contoh
```
2021-05-19 02:05:15:jack:SELECT FROM table1
```

Reliability
Harus membuat suatu program terpisah untuk dump database ke command-command yang akan di print ke layar. Untuk memasukkan ke file, gunakan redirection. Program ini tentunya harus melalui proses autentikasi terlebih dahulu. Ini sampai database level saja, tidak perlu sampai tabel. 

### Format
```
./[program_dump_database] -u [username] -p [password] [nama_database]
```

### Contoh
```
./databasedump -u jack -p jack123 database1 > database1.backup
```

Contoh hasil isi file database1.backup:
``
DROP TABLE table1;
CREATE TABLE table1 (kolom1 string, kolom2 int, kolom3 string, kolom4 int);

INSERT INTO table1 (‘abc’, 1, ‘bcd’, 2);
INSERT INTO table1 (‘abc’, 1, ‘bcd’, 2);
INSERT INTO table1 (‘abc’, 1, ‘bcd’, 2);
INSERT INTO table1 (‘abc’, 1, ‘bcd’, 2);

DROP TABLE table2;
CREATE TABLE table2 (kolom1 string, kolom2 int, kolom3 string, kolom4 int);

INSERT INTO table2 (‘abc’, 1, ‘bcd’, 2);
INSERT INTO table2 (‘abc’, 1, ‘bcd’, 2);
INSERT INTO table2 (‘abc’, 1, ‘bcd’, 2);
INSERT INTO table2 (‘abc’, 1, ‘bcd’, 2);
```
Program dump database dijalankan tiap jam untuk semua database dan log, lalu di zip sesuai timestamp, lalu log dikosongkan kembali.

Tambahan
Kita bisa memasukkan command lewat file dengan redirection di program client. 

### Format
```
./[program_client_database] -u [username] -p [password] -d [database] < [file_command]
```

### Contoh
```
./client_databaseku -u jack -p jack123 -d database1 < database.backup
```

Error Handling
Jika ada command yang tidak sesuai penggunaannya. Maka akan mengeluarkan pesan error tanpa keluar dari program client.

Extra
Program client dan dump berkomunikasi dengan socket ke program utama dan tidak boleh langsung mengakses file-file di folder program utama.
Requirement disini adalah requirement minimum, jika Anda mengerjakan melebihi requirement disini, maka akan mendapat nilai tambah.
Terapkan apa saja yang sudah kalian pelajari di praktikum sistem operasi ini untuk mengerjakan final project.
