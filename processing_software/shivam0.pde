  int a=1;
void setup()
{
  size(500,500);
}
void draw()
{ 
  background(255);
  line(0,0,500,500);
  line(0,500,500,0);
  //case 1
  if(a==1)
  {
    fill(255,0,0);
    triangle(250,20,300,150,200,150);
    fill(0,0,255);
    rect(400,250,80,80);
    fill(255,255,0);
    rect(175,400,150,80);
    fill(0,255,0);
    ellipse(100,250,100,100);
  }
  if(a==2)
  {
    fill(255,0,0);
    triangle(430,180,380,300,480,300);
    fill(0,0,255);
    rect(210,380,80,80);   
    fill(255,255,0);
    rect(30,200,150,80);
    fill(0,255,0);
    ellipse(250,120,100,100);
  }
  if(a==3)
  {
    fill(255,0,0);
    triangle(250,320,300,450,200,450);
    fill(0,0,255);
    rect(50,230,80,80);
    fill(255,255,0);
    rect(175,70,150,80);
    fill(0,255,0);
    ellipse(400,250,100,100);
  }
  if(a==4)
  {
    fill(255,0,0);
    triangle(120,180,170,300,70,300);
    fill(0,0,255);
    rect(210,100,80,80);   
    fill(255,255,0);
    rect(330,200,150,80);
    fill(0,255,0);
    ellipse(250,380,100,100);
  }
}  
void mousePressed()
{ 
  a=a+1;
  if(a==5)
  a=1;
  draw();
}  