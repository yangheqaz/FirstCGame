#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"string.h"
#include <unistd.h>

#define timers 10//��ʱ������
#define stage1_EventList 4
#define stage2_EventList 4

//���庯��
void main();
void filestart();//�ļ���ȡ
void save();//�浵����
void load();//��������
void finput();//��������ȡ����
void print_status();
void print_tutor();
void eventrandom();
void event_start();//�̳��¼�
void datechange();//���ڱ任����

void editeffect1();//�����޸�
void editeffect2();//ÿ�׶��޸�
void deathcheck();//�������


//����¼��б�
void event0();void event1();void event2();
void event3();void event4();void event5();
void event6();void event7();void event8();

//��һ�׶��¼�
void event_first();
void event_train1();
void event_train2();
void stage1_boss();

//�ڶ��׶��¼�
void event_stage2_introduction();
void event_201();
void event_221();


int HP_Max,ATT_base,SPE_base;//�׶����ֵ����
int HP,hungry,moral,care,eventaday=4;//��������
int ATT,SPE,gold,reborn;//�����������

//ϵͳ����
int date=1;//����
char input[100],player_name[100],cheatcode[100];
int flag=0,stage=1,runtime=0,Etimes=0;
int stage_fake;
int event_timesleft;

int flaga[]={1,3,3,1};//��һ�׶��¼�������ߴ���
int flagb[]={1,1,1,0};

int lock[timers]={1};timer[timers]={0};//��ʱ��

//�����б�
int eating_A;
int eating_B;
int eating_C;
int speed_up1;
int speed_up2;

FILE *p;
//������ݺ���
print_tutor()//�����������
{
    p=fopen("Tutor.txt","w");
    fprintf(p,"                                      ��ӭ�ο���Ϸ���ԣ�\n");
    fprintf(p,"                                           Author��YH\n");
    fprintf(p,"==��һ���֣���Ϸ��ֵ==\n");
    fprintf(p,"1.��ֵ����ʾ������ֵ�ͱ�ʳ�Ȳ���ֱ����ʾ��������Ӧ���ر�ע�����ǡ�\n");
    fprintf(p,"2.��ֵ�Ĺ�ϵ����ʳ���൱��Ҫ��������˵��\n");
    fprintf(p,"   1����ʳ�Ⱥ��ж����������㴦������״̬ʱ����ÿ�����4���ж����᣻������Ǳ���״̬�������5���ж����᣻������㼢��ʱ����ͽ��������ж������ˣ�\n");
    fprintf(p,"   2����ʳ�Ⱥ�����ֵ�����㴦�ھ���״̬ʱ��ÿ�����ϻ�ָ�5������ֵ�����������в����״̬�����п��ܻ�ʧȥ40������ֵ��\n");
    fprintf(p,"   3����ʳ�Ⱥ�������ֵ�����㴦�ڱ���״̬ʱ��ÿ��������΢����ս����������΢�����ƶ��ٶȣ����㴦�ڼ���״̬ʱ��ÿ�����ϻ����ս�������������ƶ��ٶȣ�\n");
    fprintf(p,"   4���¼������ı�ʳ�ȡ�ÿ���������ʧȥ5�㱥ʳ�ȡ�һ�ٷ�ԼΪ10��ʳ�ȡ�\n");
    fprintf(p,"3.������ֵ��v0.4����Ϸ�н������������ֵ����ĬĬ��¼���ѡ�񣬲��ɴ�Ӱ���¼�������ѡ����ʾ�ͽ�֣�������ע�⡣\n");
    fprintf(p,"4.v0.3�汾�Դ�һ�ű�����������Ҳ����ʧ�ܾ����ˡ�\n");
    fprintf(p,"==�ڶ����֣���Ϸ�浵==\n");
    fprintf(p,"Ŀǰ�浵�޷���¼����ĸ�����¼��˳������ؼ��¼����Լ�¼������Ҳû��ϵ��û��������������¼������¼���д�����Ҳ����˵�����������ٱ�������\n");
    fprintf(p,"�������Ҫɾ���浵��ɾ���ļ����е�Save.txt���ɡ�\n");
    fprintf(p,"==�������֣���ϵ����==\n");
    fprintf(p,"��������κκõĹ�����ƽ�����߾��齨�飬��ӭ��ϵ���ߡ�\n");
    fclose(p);
}
print_status()//״̬�������
{
    printf("��Ŀǰ��״̬���£�\n");sleep(1);
    //����״��
    if(HP>=0.9*HP_Max)
    {printf("|����״����ʮ�������ŷֽ���\n");sleep(1);}
    if(HP>=0.8*HP_Max && HP<0.9*HP_Max)
    {printf("|����״�������㽡��\n");sleep(1);}
    if(HP>=0.5*HP_Max && HP<0.8*HP_Max)
    {printf("|����״�����е�����\n");sleep(1);}
    if(HP>=0.2*HP_Max && HP<0.5*HP_Max)
    {printf("|����״�����൱����\n");sleep(1);}
    if(HP<0.2*HP_Max)
    {printf("|����״�������в���\n");sleep(1);}
    if(hungry>=90)
    {printf("|��ʳ�ȣ�����\n");sleep(1);}
    if(hungry>=70 && hungry<100)
    {printf("|��ʳ�ȣ���ʳ����\n");sleep(1);}
    if(hungry>=30 && hungry<70)
    {printf("|��ʳ�ȣ�����\n");sleep(1);}
    if(hungry>0 && hungry<30)
    {printf("|��ʳ�ȣ�����\n");sleep(1);}
    if(hungry<=0)
    {printf("|��ʳ�ȣ��ݲ�����\n");sleep(1);}
    printf("|ս��������%-4d  |��������%-4d\n",ATT,reborn);sleep(1);
    printf("|�ƶ��ٶȣ�%-4d  |��Ǯ��  %-4d\n",SPE,gold);sleep(1);

    //putchar('\n');
}
//����������ʼ��+��������
main()
{
    //��ʼ����
    srand((unsigned)time(NULL));
    HP_Max=100;ATT_base=100;SPE_base=100;
    HP=HP_Max;ATT=10;SPE=10;
    hungry=50;
    event_timesleft=eventaday;
    print_tutor();
    filestart();sleep(1);
    load();
    printf("��ã�������%s��\n\n",player_name);
    sleep(1);
    //�̴̳���
    if(runtime==0)
    {
        runtime+=1;
        event_start();
    }
    else
    {
        printf("���ڼ���������аɣ�\n\n");
        system("Pause");
        putchar('\n');
        runtime+=1;
        printf("==��%d��==\n\n",date);
    }
    //��Ϸ��ʼ
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
//�ڲ��߼�����
datechange()//�����ж�+ÿ�ս���
{
    if(event_timesleft<=0)
    {
        event_timesleft=eventaday;
        date+=1;
        editeffect1();//����
        printf("���е����ˣ�����͵���Ϊֹ�ɡ�\n\n");sleep(2);
        print_status();
        putchar('\n');
        printf("==��%d��==\n\n",date);
        system("Pause");
        putchar('\n');
    }
}
editeffect1()//ÿ���޸�,�Ѱ�����ʳ��Ӱ�졢����۳�
{
    //��ʳ��Ӱ��
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
    //����۳�
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
    //��ʱ������
    for(int i=0;i<timers;i++)
    {
        if(lock[i]!=1) timer[i]-=1;
        if(timer[i]==0) lock[i]=1;
    }
    hungry-=5;//�۳���ʳ��
    //������
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
eventrandom()//����¼�������
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
//�����������
finput()//������ȡ�������Ѿ�������1��2��3��4��-1��0
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

        else printf("���������룡\n");
    }
}
filestart()//��ȡ��Ϣ��˳��ѡ�½ڿ���
{
    p=fopen("Information.txt","r");
    if(p==NULL)
    {
        p=fopen("Information.txt","w");
        fprintf(p,"Your Name:\n");
        //fprintf(p,"Cheating Code:\n");
        printf("����һ��Ŀ¼���Information.txt�ɣ�\n\n");
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
        printf("��û����������ǳƣ���Ŀ¼���Informantion.txt��\n\n");
        system("Pause");
        exit(1);
    }
    if(!strcmp(cheatcode,"2nnd2"))
        {
            printf("�������˵ڶ��¿��֣���֪�����Ǵ��ĸ�������롭��\n\n");
            stage=2;

        }
    fclose(p);
}
save()//��Ҫ������Ϸ���д�������������Ϸ�׶Ρ���ҵ���ֵ������¼�ʣ�෢������
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
    printf("�浵�ɹ���\n");sleep(1);
}
load()//��Ҫ������Ϸ�׶Ρ������ֵ������¼�ʣ�෢������
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
//��һ�׶��¼�
event_start()//�����̳�
{
    printf("�Ƚ���һ�²����ɣ�\n\n");sleep(1);

    printf("������ʱ������st������ʾ���״̬\n\n");sleep(1);
    printf("�������ŵ���״̬���ɣ�\n");sleep(1);
    do
    {
        scanf("%s",&input);
        getchar();
        if(!strcmp(input,"st")){print_status();break;}
        else printf("���������룡\n");
    }while(1);
    putchar('\n');
    printf("�ܺã�\n\n");sleep(1);

    printf("������ʱ������save���Ա�����Ľ���\n\n");sleep(1);
    printf("�������ű�����Ȱɣ�\n");sleep(1);
    do
    {
        scanf("%s",&input);
        getchar();
        if(!strcmp(input,"save")){save();break;}
        else printf("���������룡\n");
    }while(1);
    putchar('\n');
    printf("�ܺã�\n\n");sleep(1);

    printf("֮��ֻҪ��������ѡ��Ϳ����ˣ�\n\n");sleep(1);
    printf("==== ���ס���������Ų�ס�����о�ֻ�ܽ����ˣ�====\n\n");sleep(1);
    printf("%s,���ڿ�ʼ������аɣ�\n\n",player_name);
    system("Pause");
    putchar('\n');
    printf("==��1��==\n\n");
}
event_first()//�����¼�
{
    //printf("==��1��==\n\n");
    printf("��ճ��ţ�ʦ�����ס���㡣\n\n");sleep(1);
    printf("��%s����������������޿���������㶫���߰ɣ���\n\n",player_name);sleep(1);
    printf("�㿴��һ�����ӣ���������ô����������\n\n");sleep(1);
    printf("1.Ǯ����100%%���ӽ�ң�\n");sleep(1);
    printf("2.��������100%%����ٶ����棩\n");sleep(1);
    printf("3.������100%%���ӱ�ʳ�ȡ�����ս������\n");sleep(1);
    printf("4.������ɶҲ������\n\n");sleep(1);
    printf("���ѡ�񣺣�������ż��ɣ�\n");sleep(1);
    finput();
    if(flag==1)
        {gold+=10;printf("�ɹ�����Ǯ+10\n\n");sleep(1);}
    else if(flag==2)
        {SPE+=2;speed_up1+=3;printf("�ɹ����ٶ�+2,����3��\n\n");sleep(1);}
    else if(flag==3)
        {hungry+=10;ATT+=1;eating_A+=1;printf("�ɹ����൱�ڳ����緹,��ʳ�����ӡ�ս����+1\n\n");sleep(1);}
    else if(flag==4)
    {
        printf("��ʲôҲûѡ��ֱ����·\n\n");sleep(1);
        if((rand()%101)>=90)
        {
            reborn+=1;
            printf("�������ˣ�����һ�Σ�\n\n");sleep(1);
        }
    }
    flaga[0]=0;
}
event_train1()//����¼�1
{
    printf("��������׮Ⱥ��Ҫѵ���Ṧ�𣿣�50%%���ı�ʳ�Ȼ�ȡ�ٶȣ�(y/n)\n");
    finput();
    if(flag==-1)if(rand()%101>=50)
    {
        SPE+=3;hungry-=10;
        printf("�ɹ����ٶ������3��\n\n");sleep(1);
    }
    else  printf("�����Щ��׮�Ѿ��ǳ���Ϥ�ˡ�\n\n");
    if(flag==0)printf("��ѡ���������\n\n");
    flaga[1]-=1;
}
event_train2()//����¼�2
{
    printf("������һ��ɳ����ѵ��һ��ȭ���𣿣�80%%���ı�ʳ�Ȼ�ȡ����ս������(y/n)\n");
    finput();
    if(flag==-1)if(rand()%101>=20)
    {
        hungry-=10;ATT+=6;
        printf("�ɹ������������6��\n\n");sleep(1);
    }
    else  printf("���е���и����֮ǰ��û��ʲô������\n\n");
    if(flag==0)printf("��ѡ���������\n\n");
    flaga[2]-=1;
}
stage1_boss()//��һ��boss
{
    printf("������һȺ�ٷ�!��Ҫ��ô����\n\n");sleep(1);
while(stage==1)
{
    printf("1.ս����\n");sleep(1);
    printf("2.�ӣ�\n");sleep(1);
    printf("3.ʲôҲ������\n\n");sleep(1);
    printf("4.����̸�С�\n\n");sleep(1);
    printf("==== ���棡�����¼������޷�Ԥ����ʣ�====\n\n");sleep(1);
    printf("��ʾ1����ʱ����st���鿴�����ķ��������ơ��鿴����֮��ֱ���������ѡ����ż��ɡ�\n\n");sleep(1);
    printf("��ʾ2����ʱ����save��������Ľ��ȡ��������֮��ֱ���������ѡ����ż��ɡ�\n");
    finput();
    putchar('\n');
    if(flag==1 && ATT>=22)
    {
        printf("�����ɻ��������нٷˣ������������ǵ�Ǯ������Ǯ+50��\n\n");sleep(1);
        hungry-=5;
        gold+=50;
        stage=2;
        lock[1]=0;timer[1]=1;
    }
    else if(flag==1 && ATT>10)
    {
        printf("���ܵ����ˣ�����ɹ����������������ǡ�\n\n");sleep(1);
        printf("���Ҿ����˼���ս�������ս���������ˡ���ս������+1��\n\n");sleep(1);
        hungry-=15;
        HP=0.8*HP_Max;ATT+=1;
        stage=2;
    }
    if(flag==2 && SPE>15)
    {
        printf("��ɹ����������ǵ�׷����\n\n");sleep(1);
        hungry-=20;
        stage=2;
    }
    if(flag==3 && gold>0) if(gold+rand()%101>=50)
    {
        printf("�������������Ǯ�����ڲ�û��Σ�����������\n\n");sleep(1);
        gold-=50;
        if(gold<0) gold=0;
        stage=2;
    }
    if(flag==1 && HP>=80 && ATT<=10)
    {
        printf("��Ȼ��򲻹����������㹻Ƥ����񣬻��������������������������в���\n\n");sleep(2);
        HP=0.19*HP_Max;
        stage=2;
    }
    if(flag==4)
    {
        moral=1;
        printf("�ٷ�˵�����ֵܣ�����Ҳ�ǲ����ѣ�˭Ը�������Ƶط������\n");sleep(2);
        printf("�ٷ�˵�������ڰ�Ǯȫ����������Ҫ�ٷϻ��ˡ���\n");sleep(1);
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
//�ڶ��׶��¼�
event_stage2_introduction()
{

    printf("Ϊʲô���컯��֮�»������ٷˣ���Ҳ̫����ˡ�\n\n");
    printf("1.�ұ���ȥ��֧Ԯ�������Լ������Ҿ��������˵��ġ�(2��·��)\n");
    printf("2.����˱���һ�����򵥣������ȵ���һ��\n\n");
    printf("��ʾ�����������¼�������������������κ�Ӱ�졣\n\n");
    printf("���ѡ��:\n");
    while(flagb[0])
    {
        finput();
        if(flag==1)
        {
            lock[0]=0;timer[0]=2;timer[1]=100;
            printf("�������ͽ���ׯ������\n\n");
            flagb[0]-=1;
        }
        if(flag==2)
        {
            printf("�����ص��·����ٵ���һ�顣\n\n");
            flagb[0]-=1;
            flagb[1]=1;
        }
    }

}
event_201()
{
    printf("��յ��ط����ͱ����ڹ�ľ��ľ���͵Ϯ�ˡ�\n\n");sleep(1);
    printf("�㵱�����Ʒ���������50�𶼱����ߡ�����Ǯ-50��\n\n");sleep(1);
    printf("��û����������Ǯһ�ֶ����٣���\n\n");sleep(1);
    printf("�����߾߻񣡡�\n\n");sleep(1);
    gold-=50;
    printf("ʲô�������ͽٷ˾�Ȼ��ͨһ�������ڹ�������\n\n");sleep(1);
    printf("����뷴�����ͱ�����������ˡ�\n\n");sleep(1);
    flagb[1]=0;
}
event_221()
{
    printf("��յ��ط����ͱ����ڹ�ľ��ľ���͵Ϯ�ˡ�\n\n");sleep(1);
    flagb[2]=0;
}
deathcheck()
{
    if(HP<=0 && reborn>0)
    {
        reborn-=1;
        HP=0.5*HP_Max;
        printf("���콵�¾�ˣ����㲻����\n\n");sleep(1);
    }
    else if(HP<=0)
    {
        printf("��֪��Ϊʲô����ʧ���ˣ�\n\n");sleep(1);
        printf("��һ�ν���Լ���ʵ���پ��߰ɣ�\n\n");sleep(1);
        system("Pause");
        exit(1);
    }
}
