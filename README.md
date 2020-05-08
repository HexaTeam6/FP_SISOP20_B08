# FP_SISOP20_B08
Final Project Sistem Operasi
Membuat CLI pada xv6 menggunakan C.

| Commands      | Status        |
| ------------- |-------------- |
| touch         | :heavy_check_mark: |
| rename        | :x:               | 
| chmod         | :x:               |
| mv(biasa, * ) | :heavy_check_mark: |
| tail          | :heavy_check_mark: |

Penggunaan command :
⋅⋅* touch 

⋅⋅⋅ Perintah ini digunakan untuk mengganti timestamp sebuah file ke waktu sekarang.

- rename : Mengubah nama file.
    Contoh :
    rename ‘s/.prog/.prg/’ * .prog -> mengganti nama semua file dengan ekstensi .prog
    menjadi .prg’
    rename ‘s/slang_/sl_/’ * .c -> mengganti kata slang_ dengan sl_ pada semua nama file
    dengan ekstensi .c
    rename ‘s/sl_//’ * .c -> menghilangkan kata sl_ pada semua nama file dengan ekstensi .c
    (mengganti sl_ dengan nothing )
    rename ‘s/(stri/stra)ng/bang/’ * .c’ -> mengganti kata string atau strang dengan bang
    pada semua nama file dengan ekstensi .c
    rename ‘y/a-z/A-Z/’ * .prg -> menganti semua huruf kecil menjadi huruf besar pada
    semua nama file dengan ekstensi .prg (Translations).
- chmod : Mengubah file permission suatu file atau directory.
    r = 4
    w = 2
    x = 1
    Contoh : chmod 777 tes.txt -> file permission dari tes.txt akan berubah menjadi 777 (user, group, others)
- mv(biasa, * ) : Perintah ini digunakan untuk memindahkan file-file ke folder tujuan.
- tail : Perintah tail atau tail command akan menampilkan bagian terakhir (10 baris secara default) dari 
    satu atau lebih file atau data yang disalurkan.
