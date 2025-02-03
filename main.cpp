#include <GL/glut.h>
#include <cmath>
#include <math.h>
#include <map>
using namespace std;

const int CAPSLOCK = 14;
const int LSHIFT = 15;
const int RSHIFT = 16;
const int LCTRL = 17;
const int LALT = 18;
const int RALT = 19;
const int MENU = 20;
const int RCTRL = 21;

map<char,bool>keyStates;
map<int,bool>largeKeyStates;
map<char,char> symbols;
map<int,char*> largeKeyPhrases;
const int SYMBOLS_SIZE = 21;

// Keycap constants
#define KEYCAP_SIZE 50.0f // Square keycap size
#define CORNER_RADIUS 8.0f // Radius for rounded corners
#define SEGMENTS 12 // Number of segments for rounded corners
#define KEY_SPACING 4.0f // Spacing between keycaps

// Function to draw a square keycap with rounded edges
void drawKeycap(char letter, float x, float y, float multiplier) {
    if(keyStates[letter] || keyStates[symbols[letter]]){
        glColor3f(0,0,0);
    }
    else{
        glColor3f(1,1,1);
    }



    glBegin(GL_POLYGON);

    // Define main square area excluding corners
    glVertex2f(x + CORNER_RADIUS, y);
    glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS, y);
    glVertex2f(x + multiplier*KEYCAP_SIZE, y + CORNER_RADIUS);
    glVertex2f(x + multiplier*KEYCAP_SIZE, y + KEYCAP_SIZE - CORNER_RADIUS);
    glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS, y + KEYCAP_SIZE);
    glVertex2f(x + CORNER_RADIUS, y + KEYCAP_SIZE);
    glVertex2f(x, y + KEYCAP_SIZE - CORNER_RADIUS);
    glVertex2f(x, y + CORNER_RADIUS);

    glEnd();

    // Draw rounded corners
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + CORNER_RADIUS, y + CORNER_RADIUS);
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = M_PI + (M_PI / 2.0f) * i / SEGMENTS;
        glVertex2f(x + CORNER_RADIUS + cos(angle) * CORNER_RADIUS, y + CORNER_RADIUS + sin(angle) * CORNER_RADIUS);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS, y + CORNER_RADIUS);
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = 1.5f * M_PI + (M_PI / 2.0f) * i / SEGMENTS;
        glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS + cos(angle) * CORNER_RADIUS, y + CORNER_RADIUS + sin(angle) * CORNER_RADIUS);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS, y + KEYCAP_SIZE - CORNER_RADIUS);
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = 0.0f + (M_PI / 2.0f) * i / SEGMENTS;
        glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS + cos(angle) * CORNER_RADIUS, y + KEYCAP_SIZE - CORNER_RADIUS + sin(angle) * CORNER_RADIUS);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + CORNER_RADIUS, y + KEYCAP_SIZE - CORNER_RADIUS);
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = 0.5f * M_PI + (M_PI / 2.0f) * i / SEGMENTS;
        glVertex2f(x + CORNER_RADIUS + cos(angle) * CORNER_RADIUS, y + KEYCAP_SIZE - CORNER_RADIUS + sin(angle) * CORNER_RADIUS);
    }
    glEnd();

    // Letter label (centered)
    if(keyStates[letter] || keyStates[symbols[letter]]){
        glColor3f(.5,.5,.5); //white text for top
        glRasterPos2f(x + 10, y+20);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
        if(symbols.find(letter) != symbols.end()){
            glRasterPos2f(x + 10, y+40);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, symbols[letter]);
        }
    }
    else{
        glColor3f(.5,.5,.5); // Black text for top
        glRasterPos2f(x + 10, y+20);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
        if(symbols.find(letter) != symbols.end()){
            glRasterPos2f(x + 10, y+40);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, symbols[letter]);
        }
    }
}


void drawLargeKeycap(int key, float x, float y, float multiplier) {
    if(largeKeyStates[key]){
        glColor3f(0,0,0);
    }
    else{
        glColor3f(1,1,1);
    }

    glBegin(GL_POLYGON);

    // Define main square area excluding corners
    glVertex2f(x + CORNER_RADIUS, y);
    glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS, y);
    glVertex2f(x + multiplier*KEYCAP_SIZE, y + CORNER_RADIUS);
    glVertex2f(x + multiplier*KEYCAP_SIZE, y + KEYCAP_SIZE - CORNER_RADIUS);
    glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS, y + KEYCAP_SIZE);
    glVertex2f(x + CORNER_RADIUS, y + KEYCAP_SIZE);
    glVertex2f(x, y + KEYCAP_SIZE - CORNER_RADIUS);
    glVertex2f(x, y + CORNER_RADIUS);

    glEnd();

    // Draw rounded corners
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + CORNER_RADIUS, y + CORNER_RADIUS);
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = M_PI + (M_PI / 2.0f) * i / SEGMENTS;
        glVertex2f(x + CORNER_RADIUS + cos(angle) * CORNER_RADIUS, y + CORNER_RADIUS + sin(angle) * CORNER_RADIUS);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS, y + CORNER_RADIUS);
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = 1.5f * M_PI + (M_PI / 2.0f) * i / SEGMENTS;
        glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS + cos(angle) * CORNER_RADIUS, y + CORNER_RADIUS + sin(angle) * CORNER_RADIUS);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS, y + KEYCAP_SIZE - CORNER_RADIUS);
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = 0.0f + (M_PI / 2.0f) * i / SEGMENTS;
        glVertex2f(x + multiplier*KEYCAP_SIZE - CORNER_RADIUS + cos(angle) * CORNER_RADIUS, y + KEYCAP_SIZE - CORNER_RADIUS + sin(angle) * CORNER_RADIUS);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + CORNER_RADIUS, y + KEYCAP_SIZE - CORNER_RADIUS);
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = 0.5f * M_PI + (M_PI / 2.0f) * i / SEGMENTS;
        glVertex2f(x + CORNER_RADIUS + cos(angle) * CORNER_RADIUS, y + KEYCAP_SIZE - CORNER_RADIUS + sin(angle) * CORNER_RADIUS);
    }
    glEnd();

    // Letter label (centered)
    if(largeKeyStates[key]){
        glColor3f(.5,.5,.5); //white text for top
        glRasterPos2f(x + 5, y+30);
        for (int i = 0; largeKeyPhrases[key][i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, largeKeyPhrases[key][i]);
        }
    }
    else{
        glColor3f(.5,.5,.5); // Black text for top
        glRasterPos2f(x + 5, y+30);
        for (int i = 0; largeKeyPhrases[key][i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, largeKeyPhrases[key][i]);
        }
    }
}



// Function to draw the keyboard layout
void drawKeyboard() {
    
    const float LEFTstartX = 245.0f;
    const float TOPstartY = 235.0f;
    char letter = 'A';
    float tempX = LEFTstartX;
    float tempY = TOPstartY;
    char toprowsymbols[13] = {'~','!','@','#','$','%','^','&','*','(',')','_','+'};
    for (int i = 0; i < 13; i++) { //top row
        drawKeycap(toprowsymbols[i], tempX, tempY,1);
        tempX += KEYCAP_SIZE + KEY_SPACING;
    }
    drawLargeKeycap(8,tempX,tempY,2); // backspace
    tempX = LEFTstartX;
    tempY = TOPstartY + KEYCAP_SIZE + KEY_SPACING;
    drawLargeKeycap(9,tempX,tempY,1.5); //tab
    tempX += 1.5*KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('Q',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('W',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('E',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('R',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('T',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('Y',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('U',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('I',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('O',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('P',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('{',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('}',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('|',tempX,tempY,1.5);
    tempX = LEFTstartX;
    tempY += KEYCAP_SIZE+KEY_SPACING;
    drawLargeKeycap(000,tempX,tempY,1.75);
    tempX += 1.75*KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('A',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('S',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('D',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('F',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('G',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('H',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('J',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('K',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('L',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap(':',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('"',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawLargeKeycap(13,tempX,tempY,2.33); //tab
    tempX = LEFTstartX;
    tempY += KEYCAP_SIZE+KEY_SPACING;
    drawLargeKeycap(LSHIFT,tempX,tempY,2.25);
    tempX += 2.25*KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('Z',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('X',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('C',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('V',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('B',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('N',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('M',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('<',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('>',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawKeycap('?',tempX,tempY,1);
    tempX += KEYCAP_SIZE + KEY_SPACING;
    drawLargeKeycap(000,tempX,tempY,2.91);
    tempX = LEFTstartX;
    tempY += KEYCAP_SIZE+KEY_SPACING;
    drawLargeKeycap(LCTRL,tempX,tempY,1.33);
    tempX += 1.33*KEYCAP_SIZE+KEY_SPACING;
    drawLargeKeycap(000,tempX,tempY,1.33);
    tempX += 1.33*KEYCAP_SIZE+KEY_SPACING;
    drawLargeKeycap(LALT,tempX,tempY,1.25);
    tempX += 1.25*KEYCAP_SIZE+KEY_SPACING;
    drawKeycap(32,tempX,tempY,6.25);
    tempX += 6.25*KEYCAP_SIZE+KEY_SPACING;
    drawLargeKeycap(000,tempX,tempY,1.33);
    tempX += 1.33*KEYCAP_SIZE+KEY_SPACING;
    drawLargeKeycap(000,tempX,tempY,1.33);
    tempX += 1.33*KEYCAP_SIZE+KEY_SPACING;
    drawLargeKeycap(000,tempX,tempY,1.33);
    tempX += 1.33*KEYCAP_SIZE+KEY_SPACING;
    drawLargeKeycap(000,tempX,tempY,1.33);

}
// Display callback function
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawKeyboard();
    glutSwapBuffers();
}

// Reshape callback function
void reshape(int w, int h) {
    int fixedWidth = 1280;
    int fixedHeight = 720;
    if (w != fixedWidth || h != fixedHeight) {
        glutReshapeWindow(fixedWidth, fixedHeight); // Force window back to fixed size
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, (float)w, (float)h, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyDown(unsigned char key, int x, int y){
    key = toupper(key);
    if(keyStates.find(key) != keyStates.end()){
        keyStates[key] = true;
        glutPostRedisplay();
    }
    if(key == 8){
        largeKeyStates[key] = true;
        glutPostRedisplay();

    }
    else if (key == 9) { // Tab
        largeKeyStates[key] = true;
        glutPostRedisplay();
    } else if (key == 13) { // Enter
        largeKeyStates[key] = true;
        glutPostRedisplay();
    } else if (key == 32) { // Space
        largeKeyStates[key] = true;
        glutPostRedisplay();
    }
}

void keyUp(unsigned char key, int x, int y){
    key = toupper(key);
    if(keyStates.find(key) != keyStates.end()){
        keyStates[key] = false;
        glutPostRedisplay();
    }
    if(key == 8){
        largeKeyStates[key] = false;
        glutPostRedisplay();
    }
    else if (key == 9) { // Tab
        largeKeyStates[key] = false;
        glutPostRedisplay();
    } else if (key == 13) { // Enter
        largeKeyStates[key] = false;
        glutPostRedisplay();
    } else if (key == 32) { // Space
        largeKeyStates[key] = false;
        glutPostRedisplay();
    }
}

void specialKeyDown(int key, int x, int y) {
    int mod = glutGetModifiers();
    if(mod & GLUT_ACTIVE_SHIFT){
        largeKeyStates[LSHIFT] = true;
    }
    if(mod & GLUT_ACTIVE_ALT){
        largeKeyStates[LALT] = true;
    }
    if(mod & GLUT_ACTIVE_CTRL){
        largeKeyStates[LCTRL] = true;
    }
    glutPostRedisplay();
}

void specialKeyUp(int key, int x, int y) {
    largeKeyStates[LSHIFT] = false;
    largeKeyStates[LALT]   = false;
    largeKeyStates[LCTRL]  = false;
    glutPostRedisplay();
}


void makeSymbolMap(map<char,char>& symbols){
    symbols['~'] = '`';
    symbols['!'] = '1';
    symbols['@'] = '2';
    symbols['#'] = '3';
    symbols['$'] = '4';
    symbols['%'] = '5';
    symbols['^'] = '6';
    symbols['&'] = '7';
    symbols['*'] = '8';
    symbols['('] = '9';
    symbols[')'] = '0';
    symbols['_'] = '-';
    symbols['+'] = '=';
    symbols['{'] = '[';
    symbols['}'] = ']';
    symbols['|'] = '\\';
    symbols[':'] = ';';
    symbols['"'] = '\'';
    symbols['<'] = ',';
    symbols['>'] = '.';
    symbols['?'] = '/';
}

void makeLargeKeysStateMap(map<int,bool>& largeKeyStates){
    largeKeyStates[8] = false; // backspace
    largeKeyStates[9] = false; // tab
    largeKeyStates[13] = false; // enter
    largeKeyStates[LALT] = false;  
    largeKeyStates[LSHIFT] = false;  
    largeKeyStates[LCTRL] = false; 
    largeKeyStates[000] = false;
    
}

void makeLargeKeysPhraseMap(map<int,char*>& largeKeyPhrases){
    largeKeyPhrases[8] = "Backspace";
    largeKeyPhrases[9] = "Tab";
    largeKeyPhrases[13] = "Enter";
    largeKeyPhrases[32] = "";
    largeKeyPhrases[LALT] = "Alt";
    largeKeyPhrases[LSHIFT] = "Shift";
    largeKeyPhrases[LCTRL] = "Ctrl";
    largeKeyPhrases[000] = "";

}


// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("OPEN KEYBRD SIM");
    glClearColor(.85, .85, .85, 1);
    makeSymbolMap(symbols);
    makeLargeKeysStateMap(largeKeyStates);
    makeLargeKeysPhraseMap(largeKeyPhrases);
    for(char letter = 'A';letter <= 'Z';letter++){
        keyStates[letter] = false;
    }
    for(const auto& symbolpair : symbols){
        keyStates[symbolpair.first] = false;
        keyStates[symbolpair.second] = false;
    }

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);
    glutMainLoop();
    return 0;
}
