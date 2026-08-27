## notlarım

- testerlar test edilecek(tamer + slack link)
- tester olarak bunu kullandım (https://github.com/Sfabi28/libft_tester)
- https://github.com/tamerakdeniz/libft-tester
-  ../libft-tester/libft-tester . --all --leaks   tamerinkisinde bu şekilde derledi strnstr sorun çıkardı.

- readme güncellenecek(resources güncelle, testerları da ekleyebilirisn)
- makefile dosyası düzenle
- pdf, mans, linked list tekrar edilecek. notlarınla birşeltir.(bu markdown dosyasına yaz notlrını) 

- strlcat incele(new_len eklendi)
- strnstr incele
- https://www.c-jump.com/bcc/c261c/CPU/Numbers/U77_0160_sign_extension.htm(sign extension)


# C Dilinde Tip Seçimi ve Libft Kavramları: Kapsamlı Çalışma Notu

Düşük seviyeli programlama ve standart kütüphane (`Libft`) implementasyonlarında doğru veri tipini seçmek; bellek güvenliği, mimari taşınabilirlik ve derleyici optimizasyonu açısından kritik öneme sahiptir. Bu not, tip seçimi, bellek yönetimi, dosya işlemleri, Makefile mantığı ve bağlı liste (linked list) yapılarını bir arada toplar.

---

## İçindekiler

1. [Tip Kullanım Karar Tablosu](#1-tip-kullanım-karar-tablosu)
2. [Neden `unsigned char *` ile Bellek İşlenir?](#2-neden-unsigned-char--ile-bellek-işlenir-memset-memchr-strncmp)
3. [Neden `char` Parametreleri `int` Olarak Alınır?](#3-neden-char-parametreleri-int-olarak-alınır-isalpha-toupper-putchar)
4. [`size_t` ile Geriye Sayım Tuzakları](#4-size_t-ile-geriye-sayım-tuzakları)
5. [`static` Değişkenler ve Kalıcı Bellek](#5-static-değişkenler-ve-kalıcı-bellek-get_next_line-mantığı)
6. [`void *` ve Pointer Aritmetiği Mantığı](#6-void--ve-pointer-aritmetiği-mantığı)
7. [`const` Belirteci (const-correctness)](#7-const-belirteci-const-correctness)
8. [İşaretli Tamsayı Taşması: `-(-2147483648)` Tuzağı](#8-i̇şaretli-tamsayı-taşması---2147483648-tuzağı-ft_itoa-ft_putnbr_fd)
9. [`size_t` vs `ssize_t` (Sistem Çağrısı Dönüş Değerleri)](#9-size_t-vs-ssize_t-sistem-çağrısı-dönüş-değerleri)
10. [Dosya Tanımlayıcıları (File Descriptors) ve `open()` Sistem Çağrısı](#10-dosya-tanımlayıcıları-file-descriptors-ve-open-sistem-çağrısı)
11. [Makefile Detaylı İnceleme](#11-makefile-detaylı-i̇nceleme)
12. [C Header Guard (Başlık Koruyucu) Rehberi](#12-c-header-guard-başlık-koruyucu-rehberi)
13. [Standart Kütüphane Başlıkları](#13-standart-kütüphane-başlıkları)
14. [C Dilinde Tek Yönlü Bağlı Liste (Singly Linked List)](#14-c-dilinde-tek-yönlü-bağlı-liste-singly-linked-list)
15. [Stack ve Heap: Bellek Segmentleri Mantığı](#15-stack-ve-heap-bellek-segmentleri-mantığı)

---

## 1. Tip Kullanım Karar Tablosu

| Veri Tipi | İşaret | Tipik Kullanım Alanı | `Libft` Örnekleri | Seçilme Nedeni |
| :--- | :--- | :--- | :--- | :--- |
| **`int`** | İşaretli (`signed`) | Sayısal hesaplamalar, negatif dönebilecek değerler, ASCII karakter temsili | `ft_atoi`, `ft_isalpha`, `ft_toupper` | Negatif sayıları tutabilme gereksinimi ve `EOF` (`-1`) değerini destekleme zorunluluğu. |
| **`size_t`** | İşaretsiz (`unsigned`) | Bellek boyutları, dizi uzunlukları, indeks sayaçları | `ft_strlen`, `ft_memcpy`, `ft_calloc` | Bellek adresleme limitlerini tam kapsama (64-bit sistemde 64-bit) ve negatif olamayacak büyüklükleri garanti altına alma. |
| **`unsigned char`** | İşaretsiz (`unsigned`) | Ham bayt (byte) okuma, bellek manipülasyonu | `ft_memset`, `ft_memchr`, `ft_strncmp` | 0-255 aralığındaki baytları işaret genişlemesi (*sign extension*) olmadan bit düzeyinde doğru okuma. |
| **`unsigned int`** | İşaretsiz (`unsigned`) | Kesinlikle negatif olamayacak genel tamsayılar, bit maskeleme | `ft_strmapi` (indeks), `ft_itoa_base` | Sayısal aralığı 2 katına çıkarma ve tanımsız işaret kaydırmalarını engelleme. |

---

## 2. Neden `unsigned char *` ile Bellek İşlenir? (`memset`, `memchr`, `strncmp`)

Bellek fonksiyonları genellikle parametre olarak `void *` alır ancak içeride `unsigned char *` türüne dönüştürülür:

- **İşaret Genişlemesi (*Sign Extension*) Hatası:** `char` türü bazı mimarilerde varsayılan olarak `signed` (-128 ile +127) olabilir. Örneğin `0xFF` baytı `signed char` olarak okunursa `-1` değerini alır ve `int` ile karşılaştırıldığında `0xFFFFFFFF` genişlemesine uğrar. `unsigned char` kullanıldığında ise değer her zaman `255` olarak kalır ve karşılaştırmalar doğru sonuç verir.
- **Standart Bayt Boyutu:** C standardına göre 1 baytlık ham bellek bloğunu en yalın ve taşmasız temsil eden tür `unsigned char`'dır.

---

## 3. Neden `char` Parametreleri `int` Olarak Alınır? (`isalpha`, `toupper`, `putchar`)

`ft_isalpha(int c)` gibi karakter fonksiyonlarının `char` yerine `int` kabul etmesinin iki nedeni vardır:

- **`EOF` Sabiti:** Standart girdi/çıktı fonksiyonlarında dosya sonunu belirten `EOF` değeri `-1`'dir. `unsigned char` bunu tutamaz; `signed char` ise geçerli bir `255` (`0xFF`) baytı ile çakışabilir. `int` türü tüm geçerli `unsigned char` değerlerini (0–255) ve `EOF`'u güvenle barındırır.
- **Tamsayı Yükseltmesi (*Integer Promotion*):** C dilinde fonksiyonlara parametre olarak gönderilen küçük türler (`char`, `short`) otomatik olarak `int` türüne yükseltilir. Parametreyi baştan `int` tanımlamak derleyici düzeyinde ek tip dönüşüm yükünü önler.

---

## 4. `size_t` ile Geriye Sayım Tuzakları

`size_t` işaretsiz olduğundan asla `0`'ın altına düşmez. Bu durum geriye doğru sayan döngülerde sonsuz döngüye yol açar:

```c
// YANLIŞ: i = 0 olduğunda i-- işlemi ile i = SIZE_MAX (devasa pozitif sayı) olur.
size_t i = 5;
while (i >= 0)
{
    // Sonsuz döngü!
    i--;
}

// DOĞRU:
size_t i = 5;
while (i > 0)
{
    i--;
    // İşlemler burada yapılır (i = 4, 3, 2, 1, 0)
}
```

---

## 5. `static` Değişkenler ve Bellek Mantığı

* **Kalıcı Hafıza:** Normal yerel değişkenler fonksiyon bitince silinir; `static` değişkenler program sonlanana kadar değerini korur.
* **Kapsam (Scope):** Yalnızca tanımlandığı fonksiyon içinden erişilebilir.
* **Varsayılan Değer:** Otomatik olarak `0` veya `NULL` ile başlar.
* **Kullanım Amacı:** `get_next_line` gibi fonksiyonlarda, ardışık çağrılar arasında veri kaybını önlemek ve bir önceki okumadan kalan veriyi devretmek için kullanılır.

```c
void sayac(void)
{
    static int sayi = 0; // Sadece ilk çağrıda oluşturulur
    sayi++;
    printf("%d ", sayi);
}
// 3 kez çağrılırsa çıktı: 1 2 3
```

---

## 6. `void *` ve Pointer Aritmetiği Mantığı

C standardında `void` tipi belirsiz boyuta sahiptir. Bu nedenle `void *` işaretçileri üzerinde doğrudan aritmetik (`ptr + 1`, `ptr++`) yapılamaz veya dereference (`*ptr`) edilemez:

- **Derleyici Bağımsızlığı:** GCC gibi bazı derleyiciler eklenti olarak `sizeof(void) = 1` kabul etse de, ANSI C standardında tanımsızdır ve `-Wpointer-arith` bayrağıyla hata verir.
- **Bayt Düzeyi Dönüşüm:** `void *` belleği bayt bayt işlenmek istendiğinde daima önce `unsigned char *` türüne cast edilmelidir:

```c
void *ft_memmove(void *dst, const void *src, size_t len)
{
    unsigned char       *d;
    const unsigned char *s;

    d = (unsigned char *)dst;
    s = (const unsigned char *)src;
    // Artık d[i] veya s[i] şeklinde 1 baytlık adımlarla güvenle gezilebilir.
}
```

---

## 7. `const` Belirteci (const-correctness)

Parametrelerde `const` kullanımı iki temel amaca hizmet eder:

- **Sözleşme (Contract):** `const char *s` veya `const void *src` alan bir fonksiyon, çağıran tarafa "Bu bellek alanındaki veriyi sadece okuyacağım, değiştirmeyeceğim" garantisi verir.
- **Salt Okunur (Read-Only) Bellek:** String literalleri (örneğin `"42 Istanbul"`) belleğin `.rodata` (salt okunur) segmentinde tutulur. `const` içermeyen bir fonksiyona literal gönderilirse derleyici uyarısı alınır; üzerine yazılmaya çalışılırsa Segmentation Fault (Bus Error) oluşur.

---

## 8. İşaretli Tamsayı Taşması: `-(-2147483648)` Tuzağı (`ft_itoa`, `ft_putnbr_fd`)

İki tümleyenli (*two's complement*) aritmetikte negatif aralık, pozitif aralıktan 1 fazladır:

- **INT_MIN:** `-2147483648`
- **INT_MAX:** `2147483647`

```c
// YANLIŞ: n = -2147483648 iken -n işlemi INT_MAX'i aştığı için tanımsız davranışa (UB / Overflow) girer.
if (n < 0)
    n = -n;

// DOĞRU: Değer ya 'long' türüne cast edilerek pozitife çekilir ya da -2147483648 için özel kontrol eklenir.
long num;

num = n;
if (num < 0)
    num = -num;
```

---

## 9. `size_t` vs `ssize_t` (Sistem Çağrısı Dönüş Değerleri)

`ft_putchar_fd`, `ft_putstr_fd` gibi çıktılarda ve dosya işlemlerinde `write()` / `read()` fonksiyonlarının dönüş tipleri önemlidir:

| Veri Tipi | İşaret | Tanımlandığı Başlık | Amaç |
| :--- | :--- | :--- | :--- |
| **`size_t`** | İşaretsiz (`unsigned`) | `<stddef.h>` | Boyut ve adet belirtir. Hata kodu (negatif değer) döndüremez. |
| **`ssize_t`** | İşaretli (`signed`) | `<unistd.h>` | `write()` / `read()` sistem çağrılarının dönüş tipidir. Yazılan/okunan bayt sayısını döner; hata durumunda `-1` dönebilmek için işaretli olmak zorundadır. |

---

## 10. Dosya Tanımlayıcıları (File Descriptors) ve `open()` Sistem Çağrısı

`ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd` ve `ft_putnbr_fd` gibi fonksiyonlarda yer alan `fd` parametresi, Unix tabanlı sistemlerde girdi/çıktı kaynaklarını temsil eden tamsayı indeksleridir.

### 10.1 Standart Akışlar ve Özel Dosyalar

| FD Değeri | Akış / Hedef | Tanım |
| :--- | :--- | :--- |
| **`0`** | `stdin` | Standart girdi (klavye girişi) |
| **`1`** | `stdout` | Standart çıktı (terminal ekranı) |
| **`2`** | `stderr` | Standart hata çıktısı (terminal ekranı) |
| **`3+`** | Açılan Dosyalar | `open()` sistem çağrısı ile açılan gerçek dosyalar, soketler veya borular (*pipes*) |

### 10.2 `open()` Prototipi ve Parametreleri (`<fcntl.h>`)

```c
#include <fcntl.h>

int open(const char *pathname, int flags, mode_t mode);
```

### 10.3 C Dilinde Baştaki `0` Ön Eki ve Oktal (8'lik Taban) Mantığı

C programlama dilinde bir sayısal sabitin başına yazılan ön ekler, sayının hangi tabanda yorumlanacağını belirler:

- **`0` ile başlayanlar:** 8'lik taban (*Octal*) → `0644`
- **`0x` ile başlayanlar:** 16'lık taban (*Hexadecimal*) → `0xFF`
- **Ön eksiz sayılar:** 10'luk taban (*Decimal*) → `644`

#### Neden 8'lik Taban (Octal) Kullanılır?

Unix dosya izin sisteminde her kullanıcı rolü (Owner, Group, Others) tam olarak **3 bitlik** bir alana (`r`, `w`, `x`) sahiptir:

- `r` (Read) = 4 (`100₂`)
- `w` (Write) = 2 (`010₂`)
- `x` (Execute) = 1 (`001₂`)

3 bit ile ifade edilebilecek maksimum değer 7'dir (`111₂`). 8'lik tabandaki her bir basamak (0–7), ikili sistemde **tam 3 bite** karşılık gelir.

```text
    0       6         4         4
 (Octal) (Owner)   (Group)  (Others)
           rw-       r--       r--
           ││        │         │
          110       100       100  (Binary İzin Maskesi)
```

### 10.4 `open()` Bayrakları (`flags`) — Kısa Özet

`<fcntl.h>` ile gelen bayraklar, dosyanın açılış ve işlem kurallarını belirler. Bit düzeyinde `|` operatörü ile birleştirilir.

**Temel Erişim Modları (Zorunlu — Yalnızca Biri Seçilir):**

- **`O_RDONLY`:** Dosyayı **sadece okumak** için açar.
- **`O_WRONLY`:** Dosyaya **sadece yazmak** için açar.
- **`O_RDWR`:** Dosyayı **hem okumak hem yazmak** için açar. *(Asla `O_RDONLY | O_WRONLY` yapılmaz, doğrudan `O_RDWR` kullanılır).*

**Davranış Bayrakları (İsteğe Bağlı — `|` ile Eklenir):**

- **`O_CREAT`:** Dosya yoksa **sıfırdan oluşturur**. 3. parametre olan izin modu (`0644` vb.) zorunlu hale gelir.
- **`O_TRUNC`:** Dosya zaten varsa **tüm içeriğini silip sıfırlar** (0 bayt yapar).
- **`O_APPEND`:** Mevcut veriyi silmez; her yazma işleminde imleci **dosyanın sonuna** alarak ekleme yapar.
- **`O_EXCL`:** `O_CREAT` ile kullanılır. Dosya zaten varsa hata verir (`-1`), dosyanın ilk kez oluşturulmasını garanti eder.

**En Sık Kullanılan Kalıplar:**

```c
// 1. Oku:
int fd = open("oku.txt", O_RDONLY);

// 2. Sıfırdan yaz (yoksa yarat, varsa sıfırla):
int fd = open("yaz.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

// 3. Sonuna ekle (log mantığı):
int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
```

---

## 11. Makefile Detaylı İnceleme

### 11.1 Değişkenler

- **`NAME = libft.a`** — Üretilecek statik kütüphane dosyasının adıdır.
- **`HEADER = libft.h`** — Projenin başlık dosyasıdır; bağımlılık kontrolünde kullanılır.
- **`CC = cc`** — Kullanılacak C derleyicisini belirtir (Clang/GCC).
- **`CFLAGS = -Wall -Wextra -Werror`**
  - `-Wall`: Tüm temel uyarıları açar.
  - `-Wextra`: Ekstra ayrıntılı uyarıları açar.
  - `-Werror`: Uyarıları hata sayar ve derlemeyi durdurur.
- **`SRCS = ft_atoi.c ...`** — Derlenecek tüm kaynak (.c) dosyalarının listesidir.
- **`OBJS = $(SRCS:.c=.o)`** — SRCS içindeki her `.c` uzantısını `.o` (object) uzantısına çevirir.
- **`AR = ar rcs`**
  - `ar`: Nesne dosyalarını arşivleyip paketler.
  - `r`: Dosyaları ekler veya günceller (replace).
  - `c`: Arşiv yoksa sessizce oluşturur (create).
  - `s`: Sembol indeksi ekler (hızlı arama tablosu).

### 11.2 Kurallar

- **`all: $(NAME)`** — Varsayılan kuraldır; terminalde sadece `make` yazıldığında çalışır.
- **`$(NAME): $(OBJS)`** — Tüm `.o` dosyaları oluştuktan sonra `ar rcs libft.a $(OBJS)` komutuyla kütüphaneyi paketler.
- **`%.o: %.c $(HEADER)`** — Her bir `.c` dosyasını `.o` nesne dosyasına derler.
  - `-c`: Linkleme yapmadan sadece derleme yapar.
  - `$<`: Giriş dosyası (ilgili `.c`).
  - `$@`: Çıkış hedefi (oluşacak `.o`).
- **`clean:`** — `rm -f $(OBJS)` ile derleme esnasında oluşan `.o` dosyalarını siler.
- **`fclean: clean`** — Önce `clean` kuralını çalıştırır, ardından `rm -f $(NAME)` ile `libft.a` dosyasını siler.
- **`re: fclean all`** — Sırasıyla `fclean` ve `all` çalıştırarak projeyi sıfırdan yeniden derler.
- **`.PHONY: all clean fclean re`** — Bu isimlerin gerçek birer dosya adı olmadığını, Make komutları olduğunu bildirir. Klasörde aynı isimde dosya olsa bile kuralların çalışmasını garanti eder.

---

## 12. C Header Guard (Başlık Koruyucu) Rehberi

Başlık dosyalarının (`.h`) başında ve sonunda yer alan bu yapının genel adı **Header Guard (Include Guard)**'dır.

Temel amacı: Aynı başlık dosyasının yanlışlıkla **birden fazla kez dahil edilmesini (double inclusion)** ve bu yüzden oluşacak **"yeniden tanımlama (redefinition)" derleme hatalarını önlemektir**.

### Direktiflerin Görevleri

- **`#ifndef LIBFT_H` (if not defined):**
  - Önişlemciye (Preprocessor) sorar: *"LIBFT_H adında bir makro/etiket daha önce tanımlandı mı?"*
  - Eğer **tanımlanmadıysa**, altındaki kodları okumaya devam eder.
  - Eğer **zaten tanımlandıysa**, doğrudan dosyanın en sonundaki `#endif` satırına atlar ve aradaki kodları tamamen yok sayar.
- **`#define LIBFT_H`:**
  - `#ifndef` kontrolünden geçildikten hemen sonra çalışır.
  - Önişlemciye şunu söyler: *"Artık LIBFT_H etiketini hafızana kaydet ve tanımlı olarak işaretle."*
  - Böylece dosya aynı projede 2. kez `#include "libft.h"` ile çağrılırsa `#ifndef` koşulu sağlanamaz ve içerik tekrar okunmaz.
- **`#endif`:**
  - En başta açılan `#ifndef` koşulunun bittiği sınırı çizer. Dosyanın en son satırında yer alır.

```c
#ifndef LIBFT_H
# define LIBFT_H

// ... fonksiyon prototipleri, struct tanımları ...

#endif
```

---

## 13. Standart Kütüphane Başlıkları

- **`#include <stdlib.h>` (Standard Library):**
  - Bellek yönetimi ve süreç kontrol fonksiyonları için gereklidir:
    - `malloc()`: Dinamik bellek ayırma.
    - `free()`: Ayrılan belleği serbest bırakma.
    - `exit()`: Programı sonlandırma.
    - `NULL` makrosu tanımı.
- **`#include <unistd.h>` (Unix Standard):**
  - POSIX işletim sistemi API'sine ve temel sistem çağrılarına erişim sağlar:
    - `write()`: Dosya tanıtıcısına (fd / ekrana) veri yazma.
    - `read()`: Girdi okuma.
    - `close()`: Dosya tanıtıcısını kapatma.
    - `size_t` ve `ssize_t` tür tanımları.

---

## 14. C Dilinde Tek Yönlü Bağlı Liste (Singly Linked List)

Bağlı liste, verileri bellekte yan yana (ardışık) tutmak yerine, her bir elemanın (düğüm/node) bir sonraki elemanın bellek adresini bir işaretçi (pointer) ile sakladığı doğrusal ve dinamik bir veri yapısıdır.

### 14.1 Bağlı Liste vs Dizi (Array)

| Özellik | Dizi (Array) | Bağlı Liste (Linked List) |
| :--- | :--- | :--- |
| **Bellek Yerleşimi** | Bellekte bitişik (ardışık) bloklar halinde durur. | Belleğin rastgele yerlerinde dağınık durur. |
| **Boyut Esnekliği** | Sabittir (önceden belirlenir veya `realloc` gerekir). | Tamamen dinamiktir; eleman eklendikçe `malloc` ile büyür. |
| **Başa Eleman Ekleme** | O(N) — Tüm elemanları 1 sağa kaydırmak gerekir. | O(1) — Sadece 2 pointer yönlendirilir. |
| **Rastgele Erişim** | O(1) — `arr[i]` ile doğrudan adrese gidilir. | O(N) — Baştan başlayıp tek tek ilerlemek gerekir. |

### 14.2 Düğüm (Node) Mimarisi: `t_list` Struct'ı

```c
typedef struct s_list
{
    void            *content; // Düğümün sakladığı veri (int*, char* vb.)
    struct s_list   *next;    // Bir sonraki düğümün RAM adresi (son elemanda NULL)
}   t_list;
```

```text
[Head] ──► [ content | next ] ──► [ content | next ] ──► [ content | NULL ]
```

### 14.3 Libft Fonksiyonlarının Kategorileri

1. **Düğüm Oluşturma & Ekleme:**
   - `ft_lstnew`: Yeni bir düğüm için yer ayırır (`malloc`), `content`'i atar, `next = NULL` yapar.
   - `ft_lstadd_front`: Verilen yeni düğümü listenin en başına iliştirir (`*lst = new`).
   - `ft_lstadd_back`: Listenin sonuna kadar gidip son elemanın `next` işaretçisine yeni düğümü bağlar.
2. **Bilgi Edinme & Gezinme:**
   - `ft_lstsize`: Liste sonuna (`NULL`) kadar olan toplam düğüm sayısını sayar.
   - `ft_lstlast`: Listenin `next == NULL` olan son düğümünün adresini döner.
3. **Bellek Temizleme:**
   - `ft_lstdelone`: Tek bir düğümün içeriğini (`del`) ve kendisini (`free`) serbest bırakır.
   - `ft_lstclear`: Tüm düğümleri sırayla gezerek temizler ve listenin başını (`*lst = NULL`) yapar.
4. **İterasyon & Dönüşüm:**
   - `ft_lstiter`: Listedeki tüm elemanların içeriklerine verilen fonksiyonu uygular.
   - `ft_lstmap`: Mevcut listenin elemanlarını dönüştürerek yepyeni bir bağlı liste üretir.

### 14.4 Tek Pointer (`t_list *`) vs Çift Pointer (`t_list **`)

- **`t_list *lst` (Tek Yıldız):**
  - Liste sadece okunacaksa veya üzerinde gezinilecekse kullanılır (örn: `ft_lstsize`, `ft_lstiter`).
  - Listenin orijinal baş başlangıç adresini değiştirmeye ihtiyaç yoktur.
- **`t_list **lst` (Çift Yıldız):**
  - Listenin **en başındaki elemanın adresi kalıcı olarak değiştirilecekse** kullanılır (örn: `ft_lstadd_front`, `ft_lstclear`).
  - Fonksiyona liste başını tutan pointer'ın adresi (`&head`) gönderilerek orijinal gösterici güncellenir.

---

## 15. Stack ve Heap: Bellek Segmentleri Mantığı

Bir C programı çalışırken bellek, işlevine göre farklı **segmentlere** ayrılır. `malloc`, `static`, yerel değişkenler ve string literaller aslında hep bu segmentlerden birinde yaşar. Bu bölüm, önceki bölümlerde (5, 6, 7, 14) dolaylı olarak geçen bellek davranışlarını tek bir çatı altında toplar.

### 15.1 Program Belleğinin Genel Şeması

Adres uzayı, düşük adresten yükseğe doğru kabaca şöyle sıralanır:

```text
Yüksek Adres
┌───────────────────────┐
│        Stack           │  ← Fonksiyon çağrıları, yerel değişkenler (aşağı doğru büyür)
│           ↓             │
│                         │
│           ↑             │
│         Heap            │  ← malloc/free ile yönetilen dinamik bellek (yukarı doğru büyür)
├───────────────────────┤
│    BSS (ilklendirilmemiş  │  ← static/global, değer verilmemiş (0 ile başlar)
│    static/global)        │
├───────────────────────┤
│    Data (ilklendirilmiş   │  ← static/global, değer verilmiş
│    static/global)        │
├───────────────────────┤
│  Text / Code (.rodata     │  ← Program kodu ve string literalleri (salt okunur)
│  dahil)                  │
└───────────────────────┘
Düşük Adres
```

Stack ve heap birbirine doğru büyür; aralarındaki boşluk tükenirse **stack overflow** ya da `malloc` başarısızlığı (NULL dönüşü) yaşanır.

### 15.2 Stack vs Heap Karşılaştırma Tablosu

| Özellik | **Stack** | **Heap** |
| :--- | :--- | :--- |
| **Yönetim** | Otomatik (derleyici/işletim sistemi yönetir) | Manuel (`malloc` ile ayrılır, `free` ile bırakılır) |
| **Hız** | Çok hızlı (sadece bir pointer kaydırma işlemi) | Daha yavaş (ayırıcı, boş blokları arar/yönetir) |
| **Boyut Limiti** | Küçük ve sabittir (genelde birkaç MB; `ulimit -s` ile görülür) | Sistem RAM'i / sanal bellek ile sınırlıdır, çok daha büyüktür |
| **Ömür (Lifetime)** | Fonksiyon/blok bitince otomatik silinir | Programcı `free()` çağırana kadar veya program bitene kadar yaşar |
| **Parçalanma (Fragmentation)** | Oluşmaz (LIFO — son giren ilk çıkar mantığı) | Zamanla oluşabilir (rastgele boyutlarda ayırma/bırakma) |
| **Tipik Libft Kullanımı** | `int i;`, `char buf[64];`, fonksiyon parametreleri | `ft_strdup`, `ft_substr`, `ft_lstnew`, `ft_calloc` dönüş değerleri |
| **Hata Türü** | Stack overflow (çok derin özyineleme, çok büyük yerel dizi) | Memory leak (`free` unutulursa), double free, use-after-free |

### 15.3 Kod Üzerinde Stack vs Heap

```c
void ornek(void)
{
    int     a;                 // STACK: fonksiyon bitince otomatik silinir
    char    buf[64];           // STACK: sabit boyutlu, otomatik silinir
    char    *s1;

    s1 = malloc(64);           // HEAP: fonksiyon bitse bile bellek durur
    if (!s1)
        return;                // malloc başarısız olursa NULL döner, kontrol şart
    // s1 (pointer'ın kendisi) STACK'te,
    // s1'in gösterdiği 64 baytlık alan ise HEAP'te.
    free(s1);                  // HEAP belleği elle serbest bırakılmalı
    s1 = NULL;                 // dangling pointer'ı önlemek için iyi pratik
}                               // fonksiyon burada biter, a ve buf STACK'ten silinir
```

### 15.4 Neden Libft Fonksiyonları Heap Kullanır?

`ft_strdup`, `ft_substr`, `ft_split`, `ft_itoa`, `ft_lstnew` gibi fonksiyonlar **çağırana pointer döndürür**. Eğer bu bellek stack'te ayrılsaydı, fonksiyon bittiği an o bellek geçersiz olurdu (dangling pointer) ve çağıran taraf çöp veri okurdu. Bu yüzden:

- Fonksiyon içinde `malloc` ile **heap**'te yer ayrılır.
- Bellek fonksiyon bittikten sonra da geçerliliğini korur.
- Sorumluluk çağırana geçer: döndürülen pointer **kullanım sonunda mutlaka `free()` edilmelidir**, aksi halde **memory leak** oluşur (projelerde `valgrind` veya `leaks` ile kontrol yapılır).
------
# extra

## sign extension

### 1. `unsigned char` (0 – 255) Kullanırsan Ne Olur?

* `unsigned char` negatif sayı tutamaz.
* Sistem dosya bittiğinde geriye `EOF` yani `-1` döndürmeye çalışır.
* `-1` değeri `unsigned char` içine yazıldığı an doğrudan **`255`** (`11111111`) sayısına dönüşür.
* **Sonuç:** Dosyanın bittiğini anlayamazsın; sistem dosyada `255` kodlu karakteri (ASCII tablosundaki `ÿ` karakterini) okuduğunu sanır.

---

### 2. `signed char` (-128 – +127) Kullanırsan Ne Olur?

* `signed char` evet `-1` tutabilir. Ama bu sefer başka bir çakışma çıkar:
* Dosyada gerçekten **255** (yani binary olarak `11111111`) olan bir bayt/karakter olduğunu düşün (örneğin bir resim, PDF veya metin içindeki `ÿ` harfi).
* Sen bunu `signed char` içine aldığında bilgisayar bunu **`-1`** olarak okur.
* `ch == EOF` kontrolü yaptığında, program dosyanın tam ortasında `ÿ` karakterini görür görmez **"Aaa dosya bitti!"** deyip okumayı yarıda keser.

---

### Çözüm: Neden `int` (32 bit)?

Bu çakışmayı çözmenin tek yolu, kabı büyütmektir (8 bitten 32 bite çıkmak):

| Durum | 32-Bit `int` Karşılığı (Hex / Binary) | Sayısal Değer | Anlamı |
| :--- | :--- | :---: | :--- |
| **Karakter 'A'** | `0x00000041` | `65` | Geçerli karakter |
| **Karakter 'ÿ' (255)** | `0x000000FF` | **`+255`** | Geçerli karakter |
| **`EOF` (-1)** | `0xFFFFFFFF` | **`-1`** | **Dosya Bitti Sinyali** |

Gördüğün gibi 32 bitlik `int` içinde:
* `255` karakterinin değeri **`+255`** olarak kalır.
* `EOF` ise **`-1`** olarak gelir.

İkisi birbirine asla karışmaz; bilgisayar dosyadaki gerçek `255` baytı ile dosya sonu olan `-1` sinyalini net bir şekilde ayırt eder.

hem 0 ile hem 255 arasındaki tüm pozitif sayıları hem de-1(eof) değerini aynı anda hiçbir veri kaybı ve taşma olmadan tuabilen en küçük veri tipi int'tir.

**signed char neden tercih edilir peki?** :  Bellekten tasarruf etmek ve aynı zamanda eksiye düşebilen küçük tam sayıları ($-128$ ile $+127$ arası) doğru şekilde saklayabilmek için tercih edilir.