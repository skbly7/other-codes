int a=0;
void setup()
{
  size(500,500);
}
void draw()
{
  background(255);
  fill(0);
  rect(0,30,500,40);
  stroke(255);
  line(80,30,80,70);
  line(160,30,160,70);
  line(230,30,230,70);
  line(330,30,330,70);
  fill(0,255,0);
  text("Circle", 20, 60);
  text("Triangle", 100, 60);
  text("Square", 180, 60);
  text("Rectangle", 250, 60);
  if(a==1)
{
  fill(255,0,0);
  ellipse(250,250,200,200);
}  
  if(a==2)
{
  fill(255,0,0);
  triangle(250,150,100,300,400,300);
}  
  if(a==3)
{
  fill(255,0,0);
  rect(150,150,200,200);
}
  if(a==4)
{
  fill(255,0,0);
  rect(120,150,300,200);
}  
}
void mousePressed()
{
  if( mouseX>0 && mouseX<80 && mouseY<70 && mouseY>30)
  {
  a=1;
  }
  if( mouseX>80 && mouseX<160 && mouseY<70 && mouseY>30)
  {
  a=2;
  }
  if( mouseX>160 && mouseX<230 && mouseY<70 && mouseY>30)
  {
  a=3;
   }
   if( mouseX>230 && mouseX<330 && mouseY<70 && mouseY>30)
  {
  a=4;
  }
  draw();
}
