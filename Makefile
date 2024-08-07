# Derleyici ve bayraklar
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

# Çıktı dosyasının adı
TARGET = GUI

# Kaynak dosyaları
SRC = GUI.c utils/utils.c

# Derleme hedefi
all: $(TARGET)

# Derleme kuralı
$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LIBS)

# Temizlik kuralı
clean:
	rm -f $(TARGET)

