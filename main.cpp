#include <SFML/Graphics.hpp>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<iostream>
#include <SFML/Window/Mouse.hpp>

using namespace std;
using namespace sf;

void populateFile(fstream& file);

class Board {
protected:
    bool** p = new bool*[50];
    RectangleShape** bord = new RectangleShape*[50];

public:
    Vector2f size;
    Board() {
        size.x = static_cast<float>(1000) / 50.0f;
        size.y = static_cast<float>(1000) / 50.0f;

        for (int i = 0; i < 50; i++) {
            p[i] = new bool[50];
            bord[i] = new RectangleShape[50];
        }
        for(int i = 0; i < 50; i++)
            for(int j = 0; j < 50; j++)
                p[i][j] = 0;
    }

    ~Board() {
        for (int i = 0; i < 50; i++) {
            delete[] p[i];
            delete[] bord[i];
        }
        delete[] bord;
        delete[] p;
    }

    void intializeBoolean(fstream& file) {
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) {
                char c;
                file >> c;
                if (c == '1'){
                    p[i][j] = true;
                    bord[i][j].setFillColor(Color::Red);
                } else {
                    p[i][j] = false;
                    bord[i][j].setFillColor(Color::White);
                }
                bord[i][j].setSize(size);
                bord[i][j].setPosition(i * size.x, j * size.y);
            }
        }
    }

    int functionOfDeath(int i, int j){
        int count = 0;
        if(i > 0 && j > 0 && p[i-1][j-1]){
            count++;
        }
        if(i > 0 && p[i-1][j]){
            count++;
        }
        if(i > 0 && j < 49 && p[i-1][j+1]){
            count++;
        }
        if(j > 0 && p[i][j-1]){
            count++;
        }
        if(j < 49 && p[i][j+1]){
            count++;
        }
        if(i < 49 && j > 0 && p[i+1][j-1]){
            count++;
        }
        if(i < 49 && p[i+1][j]){
            count++;
        }
        if(i < 49 && j < 49 && p[i+1][j+1]){
            count++;
        }
        if(p[i][j]){
            if(count < 2){
                return 1;
            } else if(count > 3){
                return 2;
            } else {
                return 3;
            }
        } else {
            if(count == 3){
                return 4;
            } else {
                return 0;
            }
        }
    }

    void update(){
        for(int i = 0; i < 50; i++){
            for(int j = 0; j < 50; j++){
                switch(functionOfDeath(i,j)){
                    case 1:
                        p[i][j] = false; break;
                    case 2:
                        p[i][j] = true; break;
                    case 3:
                        p[i][j] = false; break;
                    case 4:
                        p[i][j] = true; break;
                    case 0:
                        break;

                }
                if(p[i][j]){
                    bord[i][j].setFillColor(Color::Red);
                } else {
                    bord[i][j].setFillColor(Color::White);
                }
            }
        }
    }



    void draw(RenderWindow& window){
        for(int i = 0; i < 50; i++){
            for(int j = 0; j < 50; j++){
                if(p[i][j])
                    bord[i][j].setFillColor(Color::Red);
                else
                    bord[i][j].setFillColor(Color::White);
                window.draw(bord[i][j]);
            }
        }
    }
    void draw2(RenderWindow& window) {
    for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) {
                // Draw the filled rectangle
                if(p[i][j]) 
                    bord[i][j].setFillColor(Color::Red);
                else
                    bord[i][j].setFillColor(Color::White); 
                
                window.draw(bord[i][j]);
            }
        }
    }
    void initupdate(){
        for(int i = 0; i < 50; i++){
            for(int j = 0; j < 50; j++){
                if(p[i][j]){
                    bord[i][j].setFillColor(Color::Red);
                } else {
                    bord[i][j].setFillColor(Color::White);
                }
            }
        }
    }

    void initset(int i, int j) {
        p[i][j] = !p[i][j]; // Toggle the value at the specified position
    }
    void set(int i, int j){
        p[i][j] = false;
    }
    void print(fstream& file){

        for(int i = 0; i < 50; i++){
            for(int j = 0; j < 50; j++){
                file << (p[i][j] ? '1' : '0');
            }
            file << endl;
        }
    }


    
};

int main()
{
    srand(time(NULL));
    RenderWindow window(VideoMode(1000, 1000), "SFML Game");
    window.setPosition(Vector2i(500, 20));
    Color textColorRest(100,102,105);
    Color textColorActive(209,208,197);

    Text menu[3];
    string menuString[3] = {"Game of Life", "Initialize", "Exit"};
    Font font;
    if(!font.loadFromFile("font/PlayfairDisplay-ExtraBold.ttf"))
        cout << "Error loading font" << endl;
    
    int menuSelected = 1;
    for(int i = 0; i < 3; i++){
        menu[i].setFont(font);
        menu[i].setString(menuString[i]);
        if(i == 1 || i == 2){
            if(i == 1) menu[i].setFillColor(textColorActive);
            else menu[i].setFillColor(textColorRest);
            menu[i].setCharacterSize(66);   
            menu[i].setPosition(window.getSize().x / 2.0f - menu[i].getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - 120.0f + i * 100.0f);
        } else {
            menu[i].setFillColor(textColorActive);
            menu[i].setCharacterSize(100);
            menu[i].setPosition(window.getSize().x / 2.0f - menu[i].getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - 120.0f + i * 100.0f - 100.0f);
        }
    }

    Text randomText;
    randomText.setFont(font);
    randomText.setString("{Press Space to Randomize}");
    randomText.setFillColor(textColorRest);
    randomText.setCharacterSize(33);

    Text invertText;
    invertText.setFont(font);
    invertText.setString("{Press R to rest}");
    invertText.setFillColor(textColorRest);
    invertText.setCharacterSize(33);

    Text enterText;
    enterText.setFont(font);
    enterText.setString("{Press Enter to start}");
    enterText.setFillColor(textColorRest);
    enterText.setCharacterSize(33);
    
    Text cursorText;
    cursorText.setFont(font);
    cursorText.setString("{Click to select starting state}");
    cursorText.setFillColor(textColorRest);
    cursorText.setCharacterSize(33);
    randomText.setPosition(window.getSize().x / 2.0f - randomText.getGlobalBounds().width - 150.0f/ 2.0f, window.getSize().y / 2.0f - 120.0f - 350.0f);
    invertText.setPosition(window.getSize().x / 2.0f - invertText.getGlobalBounds().width - 250.0f, window.getSize().y / 2.0f - 120.0f - 300.0f );
    enterText.setPosition(window.getSize().x / 2.0f - enterText.getGlobalBounds().width - 355.0f/ 2.0f, window.getSize().y / 2.0f - 120.0f - 250.0f );
    cursorText.setPosition(window.getSize().x / 2.0f - cursorText.getGlobalBounds().width - 45.0f, window.getSize().y / 2.0f -330.0f );


    Board board;
    bool inMenu = true, init = false, start = false;
    Clock timer;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if(event.type == Event::KeyPressed){
                if(inMenu){
                    if(event.key.code == Keyboard::Up){
                        menuSelected--;
                        if(menuSelected < 1) menuSelected = 2;
                    } else if(event.key.code == Keyboard::Down){
                        menuSelected++;
                        if(menuSelected > 2) menuSelected = 1;
                    } else if(event.key.code == Keyboard::Enter){
                        if(menuSelected == 1){
                            inMenu = false; init = true;
                        } else if (menuSelected == 2){
                            window.close();
                        }
                    }
                } else if (init && !inMenu){
                    // takes u into init page
                    if(event.key.code == Keyboard::Enter){
                        // takes to start page
                        start = true;
                        init = false;
                        fstream file("config.txt");
                        board.intializeBoolean(file);
                    } else if (event.key.code == Keyboard::Escape){
                        inMenu = true; init = false; start = false;
                    } else if (event.key.code == Keyboard::R){
                        // resets the board
                            for(int i = 0; i < 50; i++){
                                for(int j = 0; j < 50; j++){
                                    board.set(i,j);
                                }
                            }
                        } else if (event.key.code == Keyboard::Space){
                            // randomizes the board
                            for(int i = 0; i < 50; i++){
                                for(int j = 0; j < 50; j++){
                                    board.initset(i,j);
                                }
                            }
                            fstream file("config.txt");
                            populateFile(file);
                            file.close();
                            fstream file2("config.txt");
                            board.intializeBoolean(file2);
                            file2.close();
                    }
                } else if (start && !inMenu && !init){
                    if(event.key.code == Keyboard::Escape){
                        inMenu = true; init = false; start = false;
                    }
                }
            } if (event.type == Event::MouseButtonPressed && init){
                    if (event.mouseButton.button == Mouse::Left) {
                        int x = Mouse::getPosition(window).x / 20;
                        int y = Mouse::getPosition(window).y / 20;
                        board.initset(x,y);
                        fstream file("config.txt");
                        board.print(file);
                        file.close();
                        cout << "mouse left x: " << x << ", mouse left y: " << y << endl << endl;
                    } 

            }
        }
        window.clear(Color::White);

        if(init && !start){
            if(timer.getElapsedTime().asSeconds() > 0.25f){
                board.initupdate();
                timer.restart();
            }
            board.draw2(window);
            window.draw(randomText);
            window.draw(invertText);
            window.draw(enterText);
            window.draw(cursorText);
        }
        if(start && !init){
            if(timer.getElapsedTime().asSeconds() > 0.25f ){
                board.update();
                timer.restart();
            }
        }

        if(inMenu && !init && !start){
            for(int i = 0; i < 3; i++){
                if(i == menuSelected){
                    menu[i].setFillColor(textColorActive);
                } else {
                    menu[i].setFillColor(textColorRest);
                }
                window.draw(menu[i]);
            }
        }
        
        // Draw your game objects here
        if(start && !init)  board.draw(window);
        window.display();
    }

    return 0;
}


void populateFile(fstream& file){
    bool** p = new bool*[50];
    for(int i = 0; i < 50; i++){
        p[i] = new bool[50];
    }
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            p[i][j] = (rand()%5 == 0);
        }
    }
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            file << (p[i][j] ? '1' : '0');
        }
        file << endl;
    }
    for(int i = 0; i < 50; i++){
        delete[] p[i];
    }
    delete[] p;
}
