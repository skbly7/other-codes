PFont font;
int num = 0,o=0;
int m=0,h=0;


void setup()
{
 size(500,500);
 font = createFont("Arial",22);
 textFont(font);
}

void draw()
{
 background(255);
 if(num==0)
 {
 fill(250,0,39);
 text("Please enter time in seconds..",80,100); 
 text(":)",80,130);
 }
 
 else{   
 fill(255,0,0);
 fill(0);
 text("User input is :"+num,100,150); 
 text("Time is :",100,180);

fill(255, 0, 255);
text(h,100,200);
text("Hours",150,200);
text(m,100,220);
text("Minutes",150,220);
text(o,100,240);
text("Seconds",150,240);
 }
}


void mousePressed() {
num=num/10;
o=num;
m=o/60;
h=m/60;
o=o%60;
m=m%60;
}

void keyPressed(){
int keyNum = Character.getNumericValue(key);
num = num*10+keyNum;
o=num;
m=o/60;
h=m/60;
o=o%60;
m=m%60;
}
