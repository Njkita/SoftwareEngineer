#include <iostream>

class Audio {
public:
    void on() { std::cout << "Аудио вкл\n"; }
    void off() { std::cout << "Аудио выкл\n"; }
    void setVolume(int lvl) { std::cout << "Громкость: " << lvl << "\n"; }
};

class Video {
public:
    void on() { std::cout << "Видео вкл\n"; }
    void off() { std::cout << "Видео выкл\n"; }
    void playMovie(const std::string& name) { std::cout << "Фильм: " << name << "\n"; }
};

class Light {
public:
    void dim(int lvl) { std::cout << "Свет: " << lvl << "%\n"; }
};

class Network {
public:
    void connect() { std::cout << "Сеть подключена\n"; }
    void disconnect() { std::cout << "Сеть отключена\n"; }
};

class Cinema {
    Audio audio;
    Video video;
    Light light;
    Network network;
public:
    void startMovie(const std::string& name) {
        std::cout << "Запуск кинотеатра...\n";
        network.connect();
        light.dim(20);
        audio.on();
        audio.setVolume(5);
        video.on();
        video.playMovie(name);
    }

    void stopMovie() {
        std::cout << "Выключение кинотеатра...\n";
        video.off();
        audio.off();
        light.dim(100);
        network.disconnect();
    }
};

int main() {
    Cinema cinema;
    cinema.startMovie("Боевик");
    std::cout << "---\n";
    cinema.stopMovie();
    return 0;
}
