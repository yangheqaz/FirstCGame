#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"string.h"
#include <unistd.h>

#define timers 10//计时器个数
#define stage1_EventList 4
#define stage2_EventList 4

//主体函数
void main();
void filestart();//文件读取
void save();//存档函数
void load();//读档函数
void finput();//玩家输入读取函数
void print_status();
void print_tutor();
void eventrandom();
void event_start();//教程事件
void datechange();//日期变换函数

void editeffect1();//按日修改
void editeffect2();//每阶段修改
void deathcheck();//死亡检测


//随机事件列表
void event0();void event1();void event2();
void event3();void event4();void event5();
void event6();void event7();void event8();

//第一阶段事件
void event_first();
void event_train1();
void event_train2();
void stage1_boss();

//第二阶段事件
void event_stage2_introduction();
void event_201();
void event_221();


int HP_Max,ATT_base,SPE_base;//阶段最大值限制
int HP,hungry,moral,care,eventaday=4;//隐藏数据
int ATT,SPE,gold,reborn;//人物表象数据

//系统变量
int date=1;//天数
char input[100],player_name[100],cheatcode[100];
int flag=0,stage=1,runtime=0,Etimes=0;
int stage_fake;
int event_timesleft;

int flaga[]={1,3,3,1};//第一阶段事件触发最高次数
int flagb[]={1,1,1,0};

int lock[timers]={1};timer[timers]={0};//计时器

//增益列表
int eating_A;
int eating_B;
int eating_C;
int speed_up1;
int speed_up2;

FILE *p;
//输出内容函数
print_tutor()//攻略输出函数
{
    p=fopen("Tutor.txt","w");
    fprintf(p,"                                      欢迎参看游戏攻略！\n");
    fprintf(p,"                                           Author：YH\n");
    fprintf(p,"==第一部分：游戏数值==\n");
    fprintf(p,"1.数值的显示：生命值和饱食度不会直接显示，所以你应该特别注意它们。\n");
    fprintf(p,"2.数值的关系：饱食度相当重要。具体来说：\n");
    fprintf(p,"   1）饱食度和行动次数：当你处于正常状态时，你每天会有4次行动机会；如果你是饱腹状态，你会有5次行动机会；但如果你饥饿时，你就仅有三次行动机会了！\n");
    fprintf(p,"   2）饱食度和生命值：当你处于均衡状态时，每天晚上会恢复5点生命值；如果你是威胁生命状态，很有可能会失去40点生命值！\n");
    fprintf(p,"   3）饱食度和其他数值：当你处于饱腹状态时，每天晚上略微增加战斗能力，略微减少移动速度；当你处于饥饿状态时，每天晚上会减少战斗能力，增加移动速度！\n");
    fprintf(p,"   4）事件会消耗饱食度。每天晚上你会失去5点饱食度。一顿饭约为10饱食度。\n");
    fprintf(p,"3.隐藏数值：v0.4的游戏中将设计有隐藏数值，会默默记录你的选择，并由此影响事件触发、选项显示和结局！还请多加注意。\n");
    fprintf(p,"4.v0.3版本自带一张保命符。不过也很难失败就是了。\n");
    fprintf(p,"==第二部分：游戏存档==\n");
    fprintf(p,"目前存档无法记录你从哪个随机事件退出。但关键事件可以记录。不过也没关系，没有输入结果的随机事件不会记录运行次数，也就是说，它还可以再被触发。\n");
    fprintf(p,"如果你想要删除存档，删除文件夹中的Save.txt即可。\n");
    fprintf(p,"==第三部分：联系作者==\n");
    fprintf(p,"如果你有任何好的规则设计建议或者剧情建议，欢迎联系作者。\n");
    fclose(p);
}
print_status()//状态输出函数
{
    printf("你目前的状态如下：\n");sleep(1);
    //身体状况
    if(HP>=0.9*HP_Max)
    {printf("|身体状况：十分甚至九分健康\n");sleep(1);}
    if(HP>=0.8*HP_Max && HP<0.9*HP_Max)
    {printf("|身体状况：还算健康\n");sleep(1);}
    if(HP>=0.5*HP_Max && HP<0.8*HP_Max)
    {printf("|身体状况：有点难受\n");sleep(1);}
    if(HP>=0.2*HP_Max && HP<0.5*HP_Max)
    {printf("|身体状况：相当不适\n");sleep(1);}
    if(HP<0.2*HP_Max)
    {printf("|身体状况：风中残烛\n");sleep(1);}
    if(hungry>=90)
    {printf("|饱食度：饱腹\n");sleep(1);}
    if(hungry>=70 && hungry<100)
    {printf("|饱食度：饮食均衡\n");sleep(1);}
    if(hungry>=30 && hungry<70)
    {printf("|饱食度：不饿\n");sleep(1);}
    if(hungry>0 && hungry<30)
    {printf("|饱食度：饥饿\n");sleep(1);}
    if(hungry<=0)
    {printf("|饱食度：摧残生命\n");sleep(1);}
    printf("|战斗能力：%-4d  |保命符：%-4d\n",ATT,reborn);sleep(1);
    printf("|移动速度：%-4d  |金钱：  %-4d\n",SPE,gold);sleep(1);

    //putchar('\n');
}
//主函数：初始化+函数调用
main()
{
    //初始化区
    srand((unsigned)time(NULL));
    HP_Max=100;ATT_base=100;SPE_base=100;
    HP=HP_Max;ATT=10;SPE=10;
    hungry=50;
    event_timesleft=eventaday;
    print_tutor();
    filestart();sleep(1);
    load();
    printf("你好，旅行者%s！\n\n",player_name);
    sleep(1);
    //教程触发
    if(runtime==0)
    {
        runtime+=1;
        event_start();
    }
    else
    {
        printf("现在继续你的旅行吧！\n\n");
        system("Pause");
        putchar('\n');
        runtime+=1;
        printf("==第%d天==\n\n",date);
    }
    //游戏开始
    while((HP!=0||reborn!=0)&& stage==1)
    {
        eventrandom();
        datechange();
    }

    while((HP!=0||reborn!=0)&& stage==2)
    {
        save();
        eventrandom();
        datechange();
    }

    //while((HP!=0||reborn!=0)&& stage==2)
        //eventrandom();
}
//内部逻辑函数
datechange()//次数判断+每日结算
{
    if(event_timesleft<=0)
    {
        event_timesleft=eventaday;
        date+=1;
        editeffect1();//结算
        printf("你有点累了，今天就到此为止吧。\n\n");sleep(2);
        print_status();
        putchar('\n');
        printf("==第%d天==\n\n",date);
        system("Pause");
        putchar('\n');
    }
}
editeffect1()//每日修改,已包括饱食度影响、增益扣除
{
    //饱食度影响
    if(hungry>=90)
        {ATT+=1;SPE-=1;eventaday=5;}
    else if(hungry>=70)
        HP+=5;
    else if(hungry<=30)
    {
        ATT-=2;
        SPE+=2;
        eventaday=3;
        if(hungry==0)
            HP-=10;
    }
    else if(hungry<0)
        HP-=40;
    else eventaday=4;
    //增益扣除
    if(eating_A>=0)
    {
        eating_A-=1;
        if(eating_A==0) ATT-=1;
    }
    if(eating_B>=0)
    {
        eating_B-=1;
        if(eating_B==0) ATT-=3;
    }
    if(eating_C>=0)
    {
        eating_C-=1;
        if(eating_C==0) ATT-=5;
    }
    if(speed_up1>=0)
    {
        speed_up1-=1;
        if(speed_up1==0) SPE-=2;
    }
    //计时器运算
    for(int i=0;i<timers;i++)
    {
        if(lock[i]!=1) timer[i]-=1;
        if(timer[i]==0) lock[i]=1;
    }
    hungry-=5;//扣除饱食度
    //最后调整
    if(ATT<0)
        ATT=0;
    if(ATT>ATT_base)
        ATT=ATT_base;
    if(SPE<0)
        SPE=0;
    if(SPE>SPE_base)
        SPE=SPE_base;
    if(hungry<0)
        hungry=0;
    if(hungry>100)
        hungry=100;
}
eventrandom()//随机事件触发器
{
    if(stage==1)
    {
        if(flaga[0]>0)
            {event_first();event_timesleft-=1;Etimes+=1;}
        else
        {
            while(1)
            {
                flag=rand()%(stage1_EventList);
                if(flag==0 && flaga[1]>0)
                    {event_train1();event_timesleft-=1;Etimes+=1;break;}
                else if(flag==1 && flaga[2]>0)
                    {event_train2();event_timesleft-=1;Etimes+=1;break;}
                else if(flag==2 && flaga[1]==0 && flaga[2]==0)
                    {stage1_boss();event_timesleft=0;Etimes+=1;deathcheck();return;}
            }
        }
    }

    if(stage==2)
    {
        if(flagb[0]>0)
            {event_stage2_introduction();Etimes+=1;}
        if(flagb[1]>0)
            {
                if(lock[1]==0 && timer[1]==0)
                    {event_201();event_timesleft-=1;Etimes+=1;}
                else if(flagb[2]>0){event_221();event_timesleft-=1;Etimes+=1;}
            }

    }

}
//输入输出函数
finput()//输入提取函数，已经包含：1、2、3、4、-1、0
{
    while(1)
    {
        scanf("%s",&input);
        getchar();
        if(!strcmp(input,"st"))     {print_status();continue;}
        else if(!strcmp(input,"save")) {save();continue;}
        else if(!strcmp(input,"1")) {flag=1;break;}
        else if(!strcmp(input,"2")) {flag=2;break;}
        else if(!strcmp(input,"3")) {flag=3;break;}
        else if(!strcmp(input,"4")) {flag=4;break;}
        else if(!strcmp(input,"y")) {flag=-1;break;}
        else if(!strcmp(input,"n")) {flag=0;break;}

        else printf("请重新输入！\n");
    }
}
filestart()//读取信息，顺带选章节开局
{
    p=fopen("Information.txt","r");
    if(p==NULL)
    {
        p=fopen("Information.txt","w");
        fprintf(p,"Your Name:\n");
        //fprintf(p,"Cheating Code:\n");
        printf("先填一下目录里的Information.txt吧！\n\n");
        system("Pause");
        exit(1);
    }
    else
    {
        fscanf(p,"Your Name:%s\n",player_name);
        fscanf(p,"Cheating Code:%s\n",cheatcode);
    }
    if(strlen(player_name)==0)
    {
        p=fopen("Information.txt","w");
        fprintf(p,"Your Name:\n");
        //fprintf(p,"Cheating Code:\n");
        printf("你没有输入你的昵称，打开目录里的Informantion.txt！\n\n");
        system("Pause");
        exit(1);
    }
    if(!strcmp(cheatcode,"2nnd2"))
        {
            printf("你启动了第二章开局，不知道你是从哪搞的作弊码……\n\n");
            stage=2;

        }
    fclose(p);
}
save()//需要保存游戏运行次数、天数、游戏阶段、玩家的数值、随机事件剩余发生次数
{
    p=fopen("Save.txt","w");
    fprintf(p,"Name:%s\n",player_name);
    fprintf(p,"Playing Time:%d\n",runtime);
    fprintf(p,"Living Days:%d\n",date);
    fprintf(p,"Event Times:%d\n",Etimes);
    fprintf(p,"Stage_fake:%d\n",(stage+3)*2*stage);

    fprintf(p,"Otherdata:%d,%d,%d,%d,%d\n",ATT,SPE,gold,reborn,hungry);
    fprintf(p,"Otherdata:%d\n",HP);
    if(stage==1)
        for(int i=0;i<stage1_EventList;i++)
            fprintf(p,"%d\n",flaga[i]);
    if(stage==2)
        for(int i=0;i<stage2_EventList;i++)
            fprintf(p,"%d\n",flagb[i]);
    //putchar('\n');
    fclose(p);
    printf("存档成功！\n");sleep(1);
}
load()//需要加载游戏阶段、玩家数值、随机事件剩余发生次数
{
    p=fopen("Save.txt","r");
    if(!feof(p))
    {
        fscanf(p,"Name:%s\n",player_name);
        fscanf(p,"Playing Time:%d\n",&runtime);
        fscanf(p,"Living Days:%d\n",&date);
        fscanf(p,"Event Times:%d\n",&Etimes);
        fscanf(p,"Stage_fake:%d\n",&stage_fake);
        fscanf(p,"Otherdata:%d,%d,%d,%d,%d\n",&ATT,&SPE,&gold,&reborn,&hungry);
        fscanf(p,"Otherdata:%d\n",&HP);
        if(stage_fake==8)
        {
            for(int i=0;i<stage1_EventList;i++)
                fscanf(p,"%d",&flaga[i]);
            stage=1;
        }
        if(stage_fake==20)
        {
            for(int i=0;i<stage2_EventList;i++)
                fscanf(p,"%d",&flagb[i]);
            stage=2;
        }
    }
    fclose(p);
}
//第一阶段事件
event_start()//操作教程
{
    printf("先介绍一下操作吧：\n\n");sleep(1);

    printf("在任意时候输入st可以显示你的状态\n\n");sleep(1);
    printf("现在试着调出状态栏吧！\n");sleep(1);
    do
    {
        scanf("%s",&input);
        getchar();
        if(!strcmp(input,"st")){print_status();break;}
        else printf("请重新输入！\n");
    }while(1);
    putchar('\n');
    printf("很好！\n\n");sleep(1);

    printf("在任意时候输入save可以保存你的进度\n\n");sleep(1);
    printf("现在试着保存进度吧！\n");sleep(1);
    do
    {
        scanf("%s",&input);
        getchar();
        if(!strcmp(input,"save")){save();break;}
        else printf("请重新输入！\n");
    }while(1);
    putchar('\n');
    printf("很好！\n\n");sleep(1);

    printf("之后只要从心做出选择就可以了！\n\n");sleep(1);
    printf("==== 请记住：如果身体撑不住，旅行就只能结束了！====\n\n");sleep(1);
    printf("%s,现在开始你的旅行吧！\n\n",player_name);
    system("Pause");
    putchar('\n');
    printf("==第1天==\n\n");
}
event_first()//出门事件
{
    //printf("==第1天==\n\n");
    printf("你刚出门，师傅便叫住了你。\n\n");sleep(1);
    printf("“%s，外面的世界无依无靠，从这带点东西走吧！”\n\n",player_name);sleep(1);
    printf("你看了一眼箱子，发现了这么几样东西：\n\n");sleep(1);
    printf("1.钱袋（100%%增加金币）\n");sleep(1);
    printf("2.足力健（100%%获得速度增益）\n");sleep(1);
    printf("3.高汤（100%%增加饱食度、增加战斗力）\n");sleep(1);
    printf("4.“老子啥也不带”\n\n");sleep(1);
    printf("你的选择：（输入序号即可）\n");sleep(1);
    finput();
    if(flag==1)
        {gold+=10;printf("成功！金钱+10\n\n");sleep(1);}
    else if(flag==2)
        {SPE+=2;speed_up1+=3;printf("成功！速度+2,持续3天\n\n");sleep(1);}
    else if(flag==3)
        {hungry+=10;ATT+=1;eating_A+=1;printf("成功！相当于吃了早饭,饱食度增加、战斗力+1\n\n");sleep(1);}
    else if(flag==4)
    {
        printf("你什么也没选，直接上路\n\n");sleep(1);
        if((rand()%101)>=90)
        {
            reborn+=1;
            printf("你真幸运，免死一次！\n\n");sleep(1);
        }
    }
    flaga[0]=0;
}
event_train1()//随机事件1
{
    printf("遇到了树桩群，要训练轻功吗？（50%%消耗饱食度换取速度）(y/n)\n");
    finput();
    if(flag==-1)if(rand()%101>=50)
    {
        SPE+=3;hungry-=10;
        printf("成功！速度提高了3！\n\n");sleep(1);
    }
    else  printf("你对这些树桩已经非常熟悉了。\n\n");
    if(flag==0)printf("你选择继续旅行\n\n");
    flaga[1]-=1;
}
event_train2()//随机事件2
{
    printf("遇到了一个沙袋，训练一下拳击吗？（80%%消耗饱食度换取大量战斗力）(y/n)\n");
    finput();
    if(flag==-1)if(rand()%101>=20)
    {
        hungry-=10;ATT+=6;
        printf("成功！力量提高了6！\n\n");sleep(1);
    }
    else  printf("你有点松懈，和之前比没有什么长进。\n\n");
    if(flag==0)printf("你选择继续旅行\n\n");
    flaga[2]-=1;
}
stage1_boss()//第一章boss
{
    printf("遇到了一群劫匪!你要怎么做？\n\n");sleep(1);
while(stage==1)
{
    printf("1.战斗！\n");sleep(1);
    printf("2.逃！\n");sleep(1);
    printf("3.什么也不做。\n\n");sleep(1);
    printf("4.尝试谈判。\n\n");sleep(1);
    printf("==== 警告！特殊事件！你无法预测概率！====\n\n");sleep(1);
    printf("提示1：随时输入st，查看你在哪方面有优势。查看数据之后直接输入你的选择序号即可。\n\n");sleep(1);
    printf("提示2：随时输入save，保存你的进度。保存进度之后直接输入你的选择序号即可。\n");
    finput();
    putchar('\n');
    if(flag==1 && ATT>=22)
    {
        printf("你轻松击败了所有劫匪，还抢到了它们的钱。（金钱+50）\n\n");sleep(1);
        hungry-=5;
        gold+=50;
        stage=2;
        lock[1]=0;timer[1]=1;
    }
    else if(flag==1 && ATT>10)
    {
        printf("你受点轻伤，但你成功用武力击溃了他们。\n\n");sleep(1);
        printf("而且经过了艰苦的战斗，你的战斗力增加了。（战斗能力+1）\n\n");sleep(1);
        hungry-=15;
        HP=0.8*HP_Max;ATT+=1;
        stage=2;
    }
    if(flag==2 && SPE>15)
    {
        printf("你成功逃离了他们的追击。\n\n");sleep(1);
        hungry-=20;
        stage=2;
    }
    if(flag==3 && gold>0) if(gold+rand()%101>=50)
    {
        printf("他们抢光了你的钱，好在并没有危及你的生命。\n\n");sleep(1);
        gold-=50;
        if(gold<0) gold=0;
        stage=2;
    }
    if(flag==1 && HP>=80 && ATT<=10)
    {
        printf("虽然你打不过，但是你足够皮糙肉厚，活了下来。不过你的生命已如风中残烛。\n\n");sleep(2);
        HP=0.19*HP_Max;
        stage=2;
    }
    if(flag==4)
    {
        moral=1;
        printf("劫匪说：“兄弟，我们也是不得已，谁愿意来这破地方生活？”\n");sleep(2);
        printf("劫匪说：“现在把钱全交出来，不要再废话了。”\n");sleep(1);
        continue;
    }
    if(stage==1)
    {
        HP=0;
        stage=2;
    }
}
    event_timesleft=0;
    putchar('\n');
}
//第二阶段事件
event_stage2_introduction()
{

    printf("为什么光天化日之下会遇到劫匪？这也太奇怪了。\n\n");
    printf("1.我必须去找支援，治疗自己，并且警告其他人当心。(2天路程)\n");
    printf("2.这帮人背后一定不简单，不妨先调查一下\n\n");
    printf("提示：这是心理事件，不会对你的身体造成任何影响。\n\n");
    printf("你的选择:\n");
    while(flagb[0])
    {
        finput();
        if(flag==1)
        {
            lock[0]=0;timer[0]=2;timer[1]=100;
            printf("你打算向就近村庄进发。\n\n");
            flagb[0]-=1;
        }
        if(flag==2)
        {
            printf("你打算回到事发地再调查一遍。\n\n");
            flagb[0]-=1;
            flagb[1]=1;
        }
    }

}
event_201()
{
    printf("你刚到地方，就被藏在灌木里的警察偷袭了。\n\n");sleep(1);
    printf("你当场被制服，抢来的50金都被夺走。（金钱-50）\n\n");sleep(1);
    printf("“没错！就是他！钱一分都不少！”\n\n");sleep(1);
    printf("“人赃具获！”\n\n");sleep(1);
    gold-=50;
    printf("什么？政府和劫匪居然串通一气？正宗狗军阀！\n\n");sleep(1);
    printf("你刚想反击，就被电击器电晕了。\n\n");sleep(1);
    flagb[1]=0;
}
event_221()
{
    printf("你刚到地方，就被藏在灌木里的警察偷袭了。\n\n");sleep(1);
    flagb[2]=0;
}
deathcheck()
{
    if(HP<=0 && reborn>0)
    {
        reborn-=1;
        HP=0.5*HP_Max;
        printf("上天降下眷顾，保你不死。\n\n");sleep(1);
    }
    else if(HP<=0)
    {
        printf("不知道为什么，你失败了！\n\n");sleep(1);
        printf("下一次结合自己的实力再决策吧！\n\n");sleep(1);
        system("Pause");
        exit(1);
    }
}
