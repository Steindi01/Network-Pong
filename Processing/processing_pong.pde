/* Original by Thomas Koberger (2012). Changes for 2 Players by Christoph Steindl (2013)
*/
 
// http://lernprocessing.wordpress.com/
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
 
int ballsize = 20;       // Balldurchmesser
float xpos, ypos;    // Position des Balles
float xspeed = random(5,6);  // Geschw. des Balls in x-Richtung
float yspeed = random(0,4);  // Geschw. des Balls in y-Richtung
int fehler1 = 0;
int fehler2 = 0;
int playerpos1, playerpos2;
boolean fehler = false;

void setup() {
  size(640, 480);
  noStroke();
  playerpos1 = height/2;
  playerpos2 = height/2;
  xpos = 45;
  ypos = playerpos1;
}
 
void draw() {
  if (fehler) {
    delay(1000);
  }
  
  background(100);
  fehler = false;
  // Bewegung des Balles
  xspeed *= 1.001;
  xpos += xspeed;
  ypos += yspeed;
   
  //damit der Ball zurückprallt (rechts, oben, unten)
  if (xpos > width-ballsize/2){
    //xspeed *= -1;
  }
  if (ypos > height-ballsize/2 || ypos < 0+ballsize/2) {
    yspeed *= -1;
  }
   
  // Begrenzung links
  if (xpos <= 30+ballsize/2) {
    if (ypos > playerpos1-50 && ypos < playerpos1+50){
      xspeed *= -1;
      yspeed += (ypos-playerpos1)/5;
    }
  }
  // Begrenzung rechts
  if (xpos >= (width - 30-ballsize/2)) {
    if (ypos > playerpos2-50 && ypos < playerpos2+50){
      xspeed *= -1;
      yspeed += (ypos-playerpos2)/5;
    }
  }
  
  //Fehler Spieler 1
  if (xpos <= 0){
    fehler1++;
    playerpos1 = height/2;
    playerpos2 = height/2;
    xpos = 50;
    ypos = playerpos1;
    xspeed = random(5,6);
    yspeed = random(0,4);
    fehler = true;
  }
  
  //Fehler Spieler 2
  if (xpos > width){
    fehler2++;
    playerpos1 = height/2;
    playerpos2 = height/2;
    xpos = width - 50;
    ypos = playerpos2;
    xspeed = random(5,6) * -1;
    yspeed = random(0,4) * -1;
    fehler = true;
  }
  
  // Bewegung Rechteck
  if (keyPressed) {
    if (key == 'q') {
      if (playerpos1 - 50 > 0) {
        playerpos1 = playerpos1 - 8;
      }
    }
    if (key == 'a') {
      if (playerpos1 + 50 < height) {
        playerpos1 = playerpos1 + 8;
      }
    }
    if (key == 'p') {
      if (playerpos2 - 50 > 0) {
        playerpos2 = playerpos2 - 8;
      }
    }
    if (key == 'l') {
      if (playerpos2 + 50 < height) {
        playerpos2 = playerpos2 + 8;
      }
    }
  }
  
  // Zeichnen des Balls und des Rechtecks
  ellipse(xpos, ypos, ballsize, ballsize);
  rect (10, playerpos1-50, 20, 100);
  rect (width-30, playerpos2-50, 20, 100);
  
  //Ausgabe Spielstand
  if (fehler) {
    displayResult(fehler1, fehler2);
  }
}

void displayResult(int f1, int f2) {
  textSize(40);
  fill(0, 0, 0);
  String result = str(f1) + " : " + str(f2);
  text(result, 10, 60);
  fill(255, 255, 255);
}
