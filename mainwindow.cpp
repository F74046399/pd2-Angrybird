#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setBackgroundBrush(QPixmap(":bg/img/Background.png").scaled(960,540));

    //setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,960,540);
    ui->graphicsView->setScene(scene);

    // Enable the event Filter
    qApp->installEventFilter(this);

    //set button
    restart= new QPushButton;
    QPixmap btn1(":/button/img/restart.png");
    QIcon pics4(btn1);
    restart->setIcon(pics4);
    restart->setGeometry(800,15,60,60);
    restart->setIconSize(btn1.rect().size()/1.6);
    restart->setMaximumSize(btn1.rect().size()/1.6);
    restart->setFlat(true);


    scene->addWidget(restart);

    exit= new QPushButton;
    QPixmap btn2(":/button/img/exit.png");
    QIcon pics5(btn2);
    exit->setIcon(pics5);
    exit->setGeometry(900,15,60,60);
    exit->setIconSize(btn2.rect().size()/1.6);
    exit->setMaximumSize(btn2.rect().size()/1.6);
    exit->setFlat(true);
     scene->addWidget(exit);


    // set score
    score=new QLabel(this);
    score->setText("<h1><font color=orange>Score:");
    score->setFont(QFont("AR Darling,30,QFont::Bold"));
    score->setGeometry(30,15,200,50);
    score->show();

    number=new QLabel(this);
    number->setText("<font color=orange>0");
    number->setFont(QFont("AR Darling,30,QFont::Bold"));
    number->setGeometry(150,15,200,50);
    number->show();

    //set health
    life1=new QLabel(this);
    life1->setText("<h1><font color=orange>Health:");
    life1->setFont(QFont("AR Darling,30,QFont::Bold"));
    life1->setGeometry(30,70,200,50);
    life1->show();

    //setting life picture
    QPixmap pics1(":/life/img/life.png");
    life[0]= new QLabel(this);
    life[1]= new QLabel(this);
    life[2]= new QLabel(this);
    life[3]= new QLabel(this);
    life[0]->setPixmap(pics1);
    life[1]->setPixmap(pics1);
    life[2]->setPixmap(pics1);
    life[3]->setPixmap(pics1);
    life[0]->setGeometry(QRect(110,70,65,65));
    life[1]->setGeometry(QRect(160,70,65,65));
    life[2]->setGeometry(QRect(210,70,65,65));
    life[3]->setGeometry(QRect(260,70,65,65));
    life[0]->show();
    life[1]->show();
    life[2]->show();
    life[3]->show();

    S1=false;
    S2=false;
    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    connect(exit,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(restart,SIGNAL(clicked(bool)),this,SLOT(Restart()));
    timer.start(100/6);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));

    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());

    // Create ground (You can edit here)
    itemList.push_back(new Land(15.0f,3.0f,32.0f,4.0f,QPixmap(":/ground/img/ground.png").scaled(width(),height()/4),world,scene));

    //Create slingshot
    QPixmap pics3(":/slingshot/img/slingshot.png");
    slingshot=new QLabel(this);
    slingshot->setPixmap(pics3);
    slingshot->setGeometry(QRect(130,320,90,90));
    slingshot->show();
    /*slingbox=new sling(6.0f,7.5f,5.0f,0.001f,world,scene);
    itemList.push_back(slingbox);*/

    // Create bird
    birdie[0] = new Bird(-0.5f,10.0f,0.25f,&timer,QPixmap(":/bird/img/r.ico").scaled(height()/12.0,height()/12.0),world,scene);
    birdie[1] = new BBird(-10.0f,12.0f,0.25f,&timer,QPixmap(":/bird/img/blue.ico").scaled(height()/12.0,height()/12.0),world,scene);
    birdie[2] = new WBird(-10.0f,14.0f,0.25f,&timer,QPixmap(":/bird/img/while.ico").scaled(height()/12.0,height()/12.0),world,scene);
    birdie[3] = new YBird(-10.0f,15.0f,0.25f,&timer,QPixmap(":/bird/img/yellow.png").scaled(height()/12.0,height()/12.0),world,scene);


    //Creat bar
    bar[0] = new Bar(23.0f,9.0f,0.9f,3.5f,&timer,QPixmap(":/barrier/img/log.png").scaled(20,130),world,scene);
    bar[1] = new Bar(28.0f,9.0f,0.9f,3.5f,&timer,QPixmap(":/barrier/img/log.png").scaled(20,130),world,scene);
    bar[2] = new Bar(17.0f,8.0f,0.9f,1.9f,&timer,QPixmap(":/barrier/img/logb.png").scaled(30,80),world,scene);

    //Create enemy
    enemy[0] = new Enemy(25.0f,10.0f,0.8f,&timer,QPixmap(":/enemy/img/pig.png").scaled(80,80),world,scene);
    enemy[1] = new Enemy(19.0f,10.0f,1.0f,&timer,QPixmap(":/enemy/img/pig.png").scaled(100,100),world,scene);

    for (int i=0;i<4;++i){

    itemList.push_back(birdie[i]);
    }
    for(int i=0;i<3;i++){
        itemList.push_back(bar[i]);
    }
    itemList.push_back(enemy[0]);
    itemList.push_back(enemy[1]);



}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{

    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    if(event->type() == QEvent::MouseButtonPress)
    {

        //std::cout << "Press !" << std::endl ;
        pigchange=false;//if pig moving
        if (mouse_event->button() == Qt::RightButton){
            if(skill==false) //use the skill
            {
                birdie[num-1]->ability();
                skill=true;
            }
        }
        if (mouse_event->button() == Qt::LeftButton){

        if(count==6)
        {
            count=1;
            done=true;
        }
        if(done==true)
        {
            if((QCursor::pos().x()>1003 && QCursor::pos().x()<1064 )&&(QCursor::pos().y()>106 && QCursor::pos().y()<169)){
                torestart=false;
                done=false;
                std::cout << "i click restart !" << std::endl ;
            }
            else{
                if(onSling==true)
                {std::cout << "wrong!" << std::endl ;
                    slingbox=new sling(6.0f,7.5f,5.0f,0.001f,world,scene);
                    itemList.push_back(slingbox);//create slingshot
                    onSling=false;
                    if(num==0){//put the bird to slingshot
                        delete birdie[0];
                        std::cout << "delete in the game(for sling)" << std::endl ;
                        alivebird[0]=1;//1 means died
                        birdie[0] = new Bird(3.5f,7.76f,0.25f,&timer,QPixmap(":/bird/img/r.ico").scaled(height()/12.0,height()/12.0),world,scene);
                        alivebird[0]=0;
                        std::cout << "new in the game(sling)" << std::endl ;
                        number->setText("<font color=orange>0");
                        shoot=false;
                        done=false;//bacause a click will enter the loop 5 times
                    }
                    else if(num==1){
                        delete birdie[1];
                        std::cout << "193" << std::endl ;
                         alivebird[1]=1;
                        birdie[1] = new BBird(3.5f,7.76f,0.25,&timer,QPixmap(":/bird/img/blue.ico").scaled(height()/12.0,height()/12.0),world,scene);
                        alivebird[1]=0;
                        shoot=false;
                        done=false;
                    }
                    else if(num==2){
                        delete birdie[2];
                         std::cout << "202" << std::endl ;
                         alivebird[2]=1;
                        birdie[2] = new WBird(3.5f,7.76f,0.25f,&timer,QPixmap(":/bird/img/while.ico").scaled(height()/12.0,height()/12.0),world,scene);
                        alivebird[2]=0;
                        shoot=false;
                        done=false;
                     }
                    else{
                        delete birdie[3];
                         std::cout << "211" << std::endl ;
                         alivebird[3]=1;
                            birdie[3] = new YBird(3.5f,7.8f,0.25f,&timer,QPixmap(":/bird/img/yellow.png").scaled(height()/12.0,height()/12.0),world,scene);
                            alivebird[3]=0;
                           shoot=false;
                            done=false;
                    }
                 }
                //launch birds
                else {
                    if(shoot==false){
                        canMove=false;
                        onSling=true;
                        shoot=true;
                        done=false;
                    }
                }
        }
        }count++;

        }
    }

    if(event->type() == QEvent::MouseMove)
    {
        //std::cout << "Move !" << std::endl ;
        //set the position of the bird with mouse
        if(canMove==false)
        {
            mouseX=QCursor::pos().x();//launch point
            mouseY=QCursor::pos().y();
            std::cout << "x" <<mouseX<< std::endl ;
            std::cout << "y" << mouseY<<std::endl ;
            birdie[num]->setTransform(b2Vec2((mouseX-480)*32/960+8,18/9-(mouseY-580)*32/960),0);
        }
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        //std::cout << "Release !" << std::endl ;
        if(canMove==false)
        {
            delete slingbox;
             std::cout << "250" << std::endl ;
            canMove=true;
            a=420-mouseY;
            b=330-mouseX;
            c=sqrt(a*a+b*b);
            Vx=(c/3)*(b/c);
            Vy=(c/3)*(a/c);
            birdie[num]->setLinearVelocity(b2Vec2(Vx,Vy));
            skill=false;
            life[3-num]->hide();
            num++;
        }
    }
    return false;

}
void MainWindow::destory()//delete the enemy and add score
{
  /* Vxe=enemy[0]->getlinearvelocity().x;
   Vye=enemy[0]->getlinearvelocity().y;
   Vxe1=enemy[1]->getlinearvelocity().x;
   Vye1=enemy[1]->getlinearvelocity().y;*/

   if(pigchange==false)
   {
       if(S1==false){

            Vxe1=enemy[1]->g_body->GetLinearVelocity().x;
            Vye1=enemy[1]->g_body->GetLinearVelocity().y;
            if(Vxe1!=0 || Vye1!=0)
             {
                  delete enemy[1];
                  std::cout << "delete in the game(big)" << std::endl ;
                    up=up+200;
                      S1=true;
              }
       }
     /*  if((Vxe1!=0 || Vye1!=0)&&S1==false)
       {
                delete enemy[1];
            std::cout << "delete in the game(big)" << std::endl ;
                up=up+200;
                S1=true;
       }*/
       if(S2==false){
           Vxe=enemy[0]->g_body->GetLinearVelocity().x;
           Vye=enemy[0]->g_body->GetLinearVelocity().y;
           if(Vxe!=0 || Vye!=0)
            {
                     delete enemy[0];
                std::cout << "delete in the game(little)" << std::endl ;
                     up=up+200;
                     S2=true;
            }
       }
      /* if((Vxe!=0 || Vye!=0)&&S2==false)
       {
                delete enemy[0];
           std::cout << "delete in the game(little)" << std::endl ;
                up=up+200;
                S2=true;
       }*/
   }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    if(S1==false || S2==false){
        destory();
        std::cout << "destory" << onSling<<std::endl ;
    }
    number->setText("<h1><font color=orange>"+QString::number(up));
    number->setFont(QFont("AR Darling,30,QFont::Bold"));
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;

}
void MainWindow::Restart()
{
    // Timer


    disconnect(&timer,SIGNAL(timeout()),this,SLOT(tick()));

    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    timer.start(100/6);

    torestart=true;
    number->setText("<font color=orange>0");
    number->setFont(QFont("AR Darling,30,QFont::Bold"));
     onSling=true;
     num=0;
     shoot=true;
     done=true;
     canMove=true;
     skill=true;
     pigchange=true;

     up=0;

     count=1;

    generateElement();
    S1=false;
    S2=false;


}
void MainWindow::generateElement()
{
    //clear
    if(onSling==false)
        delete slingbox;
    for(int i=0;i<3;i++)
        delete bar[i];

    if(S1==false)
    {
        delete enemy[1];
        std::cout << "delete by restart(big)" << std::endl ;

    }
        enemy[1] = new Enemy(19.0f,10.0f,1.0f,&timer,QPixmap(":/enemy/img/pig.png").scaled(100,100),world,scene);
       std::cout << "new by restart(big)" << std::endl ;
        itemList.push_back(enemy[1]);
        S1=true;

    if(S2==false)
    {
        delete enemy[0];
         std::cout << "delete by restart(little)" << std::endl ;
    }
        enemy[0] = new Enemy(25.0f,10.0f,0.8f,&timer,QPixmap(":/enemy/img/pig.png").scaled(80,80),world,scene);
        std::cout << "new by restart(little)" << std::endl ;
        itemList.push_back(enemy[0]);
        S2=true;


    //health
    life[0]->show();
    life[1]->show();
    life[2]->show();
    life[3]->show();
    for(int i=0;i<4;i++){
        if(alivebird[i]==0){
            delete birdie[i];
         std::cout << "delete by restart" <<i<< std::endl ;
        }
     }
    //birds
    birdie[0] = new Bird(-0.5f,10.0f,0.25f,&timer,QPixmap(":/bird/img/r.ico").scaled(height()/12.0,height()/12.0),world,scene);
    birdie[1] = new BBird(-10.0f,12.0f,0.25f,&timer,QPixmap(":/bird/img/blue.ico").scaled(height()/12.0,height()/12.0),world,scene);
    birdie[2] = new WBird(-10.0f,14.0f,0.25f,&timer,QPixmap(":/bird/img/while.ico").scaled(height()/12.0,height()/12.0),world,scene);
    birdie[3] = new YBird(-10.0f,15.0f,0.25f,&timer,QPixmap(":/bird/img/yellow.png").scaled(height()/12.0,height()/12.0),world,scene);
  std::cout << "new by restart" << std::endl ;
    //Creat bar
    bar[0] = new Bar(23.0f,9.0f,0.9f,3.5f,&timer,QPixmap(":/barrier/img/log.png").scaled(20,130),world,scene);
    bar[1] = new Bar(28.0f,9.0f,0.9f,3.5f,&timer,QPixmap(":/barrier/img/log.png").scaled(20,130),world,scene);
    bar[2] = new Bar(17.0f,8.0f,0.9f,1.9f,&timer,QPixmap(":/barrier/img/logb.png").scaled(30,80),world,scene);

    for(int i=0;i<3;i++){
        itemList.push_back(bar[i]);
    }
    for(int i=0;i<4;i++)
        itemList.push_back(birdie[i]);
}
