#define spento LOW
#define acceso HIGH

//semaforo strade
int semaforo1[] {8, 9, 10, 11, 12, 13}; // g2, v2, r2, g1, v1, r1
int semaforo2[] {2, 3, 4, 5, 6, 7}; // g1, v1, r2, g2, v2, r1
int semaforo3[] {14, 15, 16, 17, 18, 19}; // r1, v1, g1, r2, v2, g2
int semaforo4[] {24, 25, 26, 27, 28, 29}; // r1, v1, g1, r2, v2, g2

//semaforo pedoni
//ordine numeri-led: rosso, verde
int pedoni1_2[] {30, 31}; //array contente i pin del primo semaforo pedonale
int pedoni3_4[] {32, 33}; //array contente i pin del secondo semaforo pedonale
int pedoni5_6[] {34, 35}; //array contente i pin del terzo semaforo pedonale
int pedoni7_8[] {36, 37}; //array contente i pin del quarto semaforo pedonale

//bottoni (pin)
int bottone[] {50, 51, 52, 53};

//piezo (pin)
int piezo = 48;

//stati bottoni
int statobottone[4] {};

//prevMillis & currMillis per vari timer
unsigned long prevMillis = 0;
unsigned long currMillis = 0;

//intervallo iniziale
const long intv = 10000;

//contatore fase
unsigned long fase = 1; // inizia dalla fase 1 per comodita

//variabili relative ai pulsanti
bool pulsanteLetto = false;
int idxPulsante = -1; // inizia da -1 perche' 0 e' il primo indice dell'array

//variabili per sapere quale fase chiamare
bool faseSemaforoChiamata = false ;
bool fasePedoneChiamata = false;

void setup()
{
    for (int i = 0; i < 6; i++)
    {
        // semafori macchine
        pinMode(semaforo1[i], OUTPUT);
        pinMode(semaforo2[i], OUTPUT);
        pinMode(semaforo3[i], OUTPUT);
        pinMode(semaforo4[i], OUTPUT);
    }

    for (int i = 0; i < 4; i++)
    {
        // semafori pedoni
        pinMode(pedoni1_2[i], OUTPUT);
        pinMode(pedoni3_4[i], OUTPUT);
        pinMode(pedoni5_6[i], OUTPUT);
        pinMode(pedoni7_8[i], OUTPUT);
    }

    for (int i = 0; i < 4; i++)
    {
        //bottoni
        pinMode(bottone[i], OUTPUT);
    }

    //piezo
    pinMode(piezo, OUTPUT);

    prevMillis = millis();
    Serial.begin(9600);
}

void loop()
{

    //stati bottoni
    if (! pulsanteLetto)
    {
        idxPulsante = letturaPulasanti(); // prende l'indice dalla funzione
        if (idxPulsante != -1) // se l'indice e' diverso da -1 significa che ha letto un pulsante
        {
            pulsanteLetto = true; // variabile a true
        }
    }

    currMillis = millis();

    //10 secondi
    if ( (!fasePedoneChiamata && !faseSemaforoChiamata) || (currMillis - prevMillis) >= intv )
    {
        Serial.println("New phase") ;

        prevMillis = currMillis;

        if (!fasePedoneChiamata)
        {
           switch (fase)
           {
            case 1:
                if(! faseSemaforoChiamata)
                {
                    Serial.println("esegue 1");
                    fase1();
                    faseSemaforoChiamata = true ;
                }
                else
                {
                    Serial.println("annulla 1");
                    annullaFase1();
                    faseSemaforoChiamata = false ;
                    fase++;
                }
                break;

            case 2:
                if(! faseSemaforoChiamata)
                {
                    Serial.println("esegue 2");
                    fase2();
                    faseSemaforoChiamata = true ;
                }
                else
                {
                    Serial.println("annulla 2");
                    annullaFase2();
                    faseSemaforoChiamata = false ;
                    fase++;
                }
                break;

            case 3:
                if(! faseSemaforoChiamata)
                {
                    Serial.println("esegue 3");
                    fase3();
                    faseSemaforoChiamata = true ;
                }
                else
                {
                    Serial.println("annulla 3");
                    annullaFase3();
                    faseSemaforoChiamata = false ;
                    fase++;
                }
                break;

            case 4:
                if(! faseSemaforoChiamata)
                {
                    Serial.println("esegue 4");
                    fase4();
                    faseSemaforoChiamata = true ;
                }
                else
                {
                    Serial.println("annulla 4");
                    annullaFase4();
                    faseSemaforoChiamata = false ;
                    fase++;
                }
                break;

            case 5:
                if(! faseSemaforoChiamata)
                {
                    Serial.println("esegue 5");
                    fase5();
                    faseSemaforoChiamata = true ;
                }
                else
                {
                    Serial.println("annulla 5");
                    annullaFase5();
                    faseSemaforoChiamata = false ;
                    fase++;
                }
                break;

            case 6:
                if(! faseSemaforoChiamata)
                {
                    Serial.println("esegue 6");
                    fase6();
                    faseSemaforoChiamata = true ;
                }
                else
                {
                    Serial.println("annulla 6");
                    annullaFase6();
                    faseSemaforoChiamata = false ;
                    fase++;
                }
                break;

            case 7:
                if(! faseSemaforoChiamata)
                {
                    Serial.println("esegue 7");
                    fase7();
                    faseSemaforoChiamata = true ;
                }
                else
                {
                    Serial.println("annulla 7");
                    annullaFase7();
                    faseSemaforoChiamata = false ;
                    fase++;
                }
                break;

            case 8:
                if(! faseSemaforoChiamata)
                {
                    Serial.println("esegue 8");
                    fase8();
                    faseSemaforoChiamata = true ;
                }
                else
                {
                    Serial.println("annulla 8");
                    annullaFase8();
                    faseSemaforoChiamata = false ;
                    fase++;
                }
                break;

            default:
                fase = 1;
                break;
            }
        }

        if(pulsanteLetto) //gestione semafori pedonali attivata solo con la lettura del pulsante
        {
           //Serial.println("pedone");
 
           switch (idxPulsante + 1) //aggiunge 1 all'indice del pulsante per comodita'
           {
            case 1:
                if (! fasePedoneChiamata) //fase pedone non chiamata, variabile a False
                {
                    fasePedone1(); //chiamata fase pedone
                    fasePedoneChiamata = true; //fase pedone a True
                }
                else //fase pedone gia chiamata
                {
                    finePedone1(); //annulla fase pedone perche' finita
                    fasePedoneChiamata = false; //fase pedone a false cosi' che si possa chiamare un'altra fase pedone successivamente
                    pulsanteLetto = false; //pulsante a false cosi che si possa leggere di nuovo
                }
                break;

            case 2:
                if (! fasePedoneChiamata)
                {
                    fasePedone2();
                    fasePedoneChiamata = true;
                }
                else
                {
                    finePedone2();
                    fasePedoneChiamata = false;
                    pulsanteLetto = false;
                }
                break;

            case 3:
                if (! fasePedoneChiamata)
                {
                    fasePedone3();
                    fasePedoneChiamata = true;
                }
                else
                {
                    finePedone3();
                    fasePedoneChiamata = false;
                    pulsanteLetto = false;
                }
                break;

            case 4:
                if (! fasePedoneChiamata)
                {
                    fasePedone4();
                    fasePedoneChiamata = true;
                }
                else
                {
                    finePedone4();
                    fasePedoneChiamata = false;
                    pulsanteLetto = false;
                }
                break;
            }
        }
    }
}


// fasi principali
void fase1()
{
    digitalWrite(semaforo1[1], acceso);//1dx        (verde 1)
    digitalWrite(semaforo1[4], acceso);//1sxdr      (verde 2)
    digitalWrite(semaforo2[1], acceso);//2dx        (verde 1)
    digitalWrite(semaforo2[2], acceso);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], acceso);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], acceso);//3sx        (rosso 2)
    digitalWrite(semaforo4[0], acceso);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[3], acceso);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], acceso);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], acceso);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], acceso);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], acceso);//4p         (rosso, buzzer non attivo)
}

void fase2()
{
    digitalWrite(semaforo1[5], acceso);//1dx        (rosso 1)
    digitalWrite(semaforo1[1], acceso);//1sxdr      (verde 2)
    digitalWrite(semaforo2[5], acceso);//2dx        (rosso 1)
    digitalWrite(semaforo2[2], acceso);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], acceso);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], acceso);//3sx        (rosso 2)
    digitalWrite(semaforo4[0], acceso);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[3], acceso);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], acceso);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[1], acceso);//2p         (verde, buzzer attivo)
    digitalWrite(pedoni5_6[0], acceso);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], acceso);//4p         (rosso, buzzer non attivo)

    alternaPiezo(); //accende buzzer per pedone3_4
    
    

}

void fase3()
{
    digitalWrite(semaforo1[4], acceso);//1dx        (verde 1)
    digitalWrite(semaforo1[2], acceso);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], acceso);//2dx        (verde 1)
    digitalWrite(semaforo2[2], acceso);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], acceso);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], acceso);//3sx        (verde 2)
    digitalWrite(semaforo4[0], acceso);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[4], acceso);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], acceso);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], acceso);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], acceso);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[1], acceso);//4p         (verde, buzzer attivo)
    alternaPiezo(); //accende piezo su semaforo 4  pedoni
}

void fase4()
{
    digitalWrite(semaforo1[1], acceso);//1dx        (verde 1)
    digitalWrite(semaforo1[5], acceso);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], acceso);//2dx        (verde 1)
    digitalWrite(semaforo2[2], acceso);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[1], acceso);//3dxdr      (verde 1)
    digitalWrite(semaforo3[4], acceso);//3sx        (verde 2)
    digitalWrite(semaforo4[0], acceso);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[3], acceso);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], acceso);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], acceso);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], acceso);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], acceso);//4p         (rosso, buzzer non attivo)
}

void fase5()
{
    digitalWrite(semaforo1[5], acceso);//1dx        (rosso 1)
    digitalWrite(semaforo1[2], acceso);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], acceso);//2dx        (verde 1)
    digitalWrite(semaforo2[4], acceso);//2sxdr      (verde 2)
    digitalWrite(semaforo3[0], acceso);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], acceso);//3sx        (rosso 2)
    digitalWrite(semaforo4[1], acceso);//4dxdr      (verde 1)
    digitalWrite(semaforo4[4], acceso);//4sx        (verde 2)

    digitalWrite(pedoni1_2[0], acceso);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], acceso);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], acceso);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], acceso);//4p         (rosso, buzzer non attivo)
}

void fase6()
{
    digitalWrite(semaforo1[4], acceso);//1dx        (verde 1)
    digitalWrite(semaforo1[2], acceso);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], acceso);//2dx        (verde 1)
    digitalWrite(semaforo2[4], acceso);//2sxdr      (verde 2)
    digitalWrite(semaforo3[0], acceso);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], acceso);//3sx        (rosso 2)
    digitalWrite(semaforo4[0], acceso);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[3], acceso);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], acceso);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], acceso);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], acceso);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], acceso);//4p         (rosso, buzzer non attivo)
}

void fase7()
{
    digitalWrite(semaforo1[5], acceso);//1dx        (rosso 1)
    digitalWrite(semaforo1[2], acceso);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], acceso);//2dx        (verde 1)
    digitalWrite(semaforo2[2], acceso);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], acceso);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], acceso);//3sx        (rosso 2)
    digitalWrite(semaforo4[0], acceso);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[4], acceso);//4sx        (verde 2)

    digitalWrite(pedoni1_2[1], acceso);//1p         (verde, buzzer attivo)
    digitalWrite(pedoni3_4[0], acceso);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], acceso);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], acceso);//4p         (rosso, buzzer non attivo)

    alternaPiezo(); //accende buzzer per pedone1_2
}

void fase8()
{
    digitalWrite(semaforo1[4], acceso);//1dx        (verde 1)
    digitalWrite(semaforo1[2], acceso);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[5], acceso);//2dx        (rosso 1)
    digitalWrite(semaforo2[2], acceso);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], acceso);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], acceso);//3sx        (rosso 2)
    digitalWrite(semaforo4[1], acceso);//4dxdr      (verde 1)
    digitalWrite(semaforo4[3], acceso);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], acceso);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], acceso);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[1], acceso);//3p         (verde, buzzer attivo)
    digitalWrite(pedoni7_8[0], acceso);//4p         (rosso, buzzer non attivo)

    alternaPiezo(); //accende buzzer per pedone 5_6
}


// annulla fasi principali
void annullaFase1()
{
    digitalWrite(semaforo1[1], spento);//1dx        (verde 1)
    digitalWrite(semaforo1[4], spento);//1sxdr      (verde 2)
    digitalWrite(semaforo1[2], acceso);//1dx        (giallo 1)
    digitalWrite(semaforo1[3], acceso);//1sxdr      (giallo 2)
    digitalWrite(semaforo2[1], spento);//2dx        (verde 1)
    digitalWrite(semaforo2[2], spento);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], spento);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], spento);//3sx        (rosso 2)
    digitalWrite(semaforo4[0], spento);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[3], spento);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], spento);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], spento);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], spento);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], spento);//4p         (rosso, buzzer non attivo)
}

void annullaFase2()
{
    digitalWrite(semaforo1[5], spento);//1dx        (rosso 1)
    digitalWrite(semaforo1[1], spento);//1sxdr      (verde 2)
    digitalWrite(semaforo2[5], spento);//2dx        (rosso 1)
    digitalWrite(semaforo2[2], spento);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], spento);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], spento);//3sx        (rosso 2)
    digitalWrite(semaforo4[0], spento);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[3], spento);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], spento);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[1], spento);//2p         (verde, buzzer attivo)
    digitalWrite(pedoni5_6[0], spento);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], spento);//4p         (rosso, buzzer non attivo)
}

void annullaFase3()
{
    digitalWrite(semaforo1[4], spento);//1dx        (verde 1)
    digitalWrite(semaforo1[2], spento);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], spento);//2dx        (verde 1)
    digitalWrite(semaforo2[2], spento);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], spento);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], spento);//3sx        (verde 2)
    digitalWrite(semaforo4[0], spento);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[4], spento);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], spento);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], spento);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], spento);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[1], spento);//4p         (verde, buzzer attivo)
}

void annullaFase4()
{
    digitalWrite(semaforo1[1], spento);//1dx        (verde 1)
    digitalWrite(semaforo1[5], spento);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], spento);//2dx        (verde 1)
    digitalWrite(semaforo2[2], spento);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[1], spento);//3dxdr      (verde 1)
    digitalWrite(semaforo3[4], spento);//3sx        (verde 2)
    digitalWrite(semaforo4[0], spento);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[3], spento);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], spento);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], spento);//2p         (verde, buzzer non attivo)
    digitalWrite(pedoni5_6[0], spento);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], spento);//4p         (rosso, buzzer non attivo)
}

void annullaFase5()
{
    digitalWrite(semaforo1[5], spento);//1dx        (rosso 1)
    digitalWrite(semaforo1[2], spento);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], spento);//2dx        (verde 1)
    digitalWrite(semaforo2[4], spento);//2sxdr      (verde 2)
    digitalWrite(semaforo3[0], spento);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], spento);//3sx        (rosso 2)
    digitalWrite(semaforo4[1], spento);//4dxdr      (verde 1)
    digitalWrite(semaforo4[4], spento);//4sx        (verde 2)

    digitalWrite(pedoni1_2[0], spento);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], spento);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], spento);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], spento);//4p         (rosso, buzzer non attivo)
}

void annullaFase6()
{
    digitalWrite(semaforo1[4], spento);//1dx        (verde 1)
    digitalWrite(semaforo1[2], spento);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], spento);//2dx        (verde 1)
    digitalWrite(semaforo2[4], spento);//2sxdr      (verde 2)
    digitalWrite(semaforo3[0], spento);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], spento);//3sx        (rosso 2)
    digitalWrite(semaforo4[0], spento);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[3], spento);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], spento);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], spento);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], spento);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], spento);//4p         (rosso, buzzer non attivo)
}

void annullaFase7()
{
    digitalWrite(semaforo1[5], spento);//1dx        (rosso 1)
    digitalWrite(semaforo1[2], spento);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], spento);//2dx        (verde 1)
    digitalWrite(semaforo2[2], spento);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], spento);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], spento);//3sx        (rosso 2)
    digitalWrite(semaforo4[0], spento);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[4], spento);//4sx        (verde 2)

    digitalWrite(pedoni1_2[1], spento);//1p         (verde, buzzer attivo)
    digitalWrite(pedoni3_4[0], spento);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], spento);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], spento);//4p         (rosso, buzzer non attivo)
}

void annullaFase8()
{
    digitalWrite(semaforo1[4], spento);//1dx        (verde 1)
    digitalWrite(semaforo1[2], spento);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[5], spento);//2dx        (rosso 1)
    digitalWrite(semaforo2[2], spento);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], spento);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], spento);//3sx        (rosso 2)
    digitalWrite(semaforo4[1], spento);//4dxdr      (verde 1)
    digitalWrite(semaforo4[3], spento);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], spento);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], spento);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[1], spento);//3p         (verde, buzzer attivo)
    digitalWrite(pedoni7_8[0], spento);//4p         (rosso, buzzer non attivo)
}


// fasi pedone
void fasePedone1()
{
    digitalWrite(semaforo1[5], acceso);//1dx        (rosso 1)
    digitalWrite(semaforo1[2], acceso);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], acceso);//2dx        (verde 1)
    digitalWrite(semaforo2[2], acceso);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], acceso);//3dxdr      (rosso 2)
    digitalWrite(semaforo3[3], acceso);//3sx        (rosso 1)
    digitalWrite(semaforo4[0], acceso);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[4], acceso);//4sx        (verde 2)

    digitalWrite(pedoni1_2[1], acceso);//1p         (verde, buzzer attivo)
    digitalWrite(pedoni3_4[0], acceso);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], acceso);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], acceso);//4p         (rosso, buzzer non attivo)

    alternaPiezo(); //accende buzzer per pedone1_2
}

void fasePedone2()
{
    digitalWrite(semaforo1[5], acceso);//1dx        (rosso 1)
    digitalWrite(semaforo1[2], acceso);//1sxdr      (verde 2)
    digitalWrite(semaforo2[5], acceso);//2dx        (rosso 1)
    digitalWrite(semaforo2[2], acceso);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], acceso);//3dxdr      (rosso 1)
    digitalWrite(semaforo3[3], acceso);//3sx        (rosso 2)
    digitalWrite(semaforo4[0], acceso);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[3], acceso);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], acceso);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[1], acceso);//2p         (verde, buzzer attivo)
    digitalWrite(pedoni5_6[0], acceso);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], acceso);//4p         (rosso, buzzer non attivo)

    alternaPiezo(); //accende buzzer per pedone3_4
}

void fasePedone3()
{
    digitalWrite(semaforo1[4], acceso);//1dx        (verde 1)
    digitalWrite(semaforo1[2], acceso);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[5], acceso);//2dx        (rosso 1)
    digitalWrite(semaforo2[2], acceso);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[3], acceso);//3dxdr      (rosso 2)
    digitalWrite(semaforo3[0], acceso);//3sx        (rosso 1)
    digitalWrite(semaforo4[1], acceso);//4dxdr      (verde 1)
    digitalWrite(semaforo4[3], acceso);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], acceso);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], acceso);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[1], acceso);//3p         (verde, buzzer attivo)
    digitalWrite(pedoni7_8[0], acceso);//4p         (rosso, buzzer non attivo)

    alternaPiezo(); //accende buzzer per pedone5_6
}

void fasePedone4()
{
    digitalWrite(semaforo1[4], acceso);//1dx        (verde 1)
    digitalWrite(semaforo1[2], acceso);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], acceso);//2dx        (verde 1)
    digitalWrite(semaforo2[2], acceso);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], acceso);//3dxdr      (nulla 1, rosso 1)
    digitalWrite(semaforo3[4], acceso);//3sx        (verde 2)
    digitalWrite(semaforo4[0], acceso);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[3], acceso);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], acceso);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], acceso);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], acceso);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[1], acceso);//4p         (verde, buzzer attivo)
    
    alternaPiezo(); //accende buzzer per pedone7_8
}


// annulla fasi pedone
void finePedone1()
{
    digitalWrite(semaforo1[5], spento);//1dx        (rosso 1)
    digitalWrite(semaforo1[2], spento);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], spento);//2dx        (verde 1)
    digitalWrite(semaforo2[2], spento);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], spento);//3dxdr      (rosso 2)
    digitalWrite(semaforo3[3], spento);//3sx        (rosso 1)
    digitalWrite(semaforo4[0], spento);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[4], spento);//4sx        (verde 2)

    digitalWrite(pedoni1_2[1], spento);//1p         (verde, buzzer attivo)
    digitalWrite(pedoni3_4[0], spento);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], spento);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], spento);//4p         (rosso, buzzer non attivo)
}

void finePedone2()
{
    digitalWrite(semaforo1[5], spento);//1dx        (rosso 1)
    digitalWrite(semaforo1[2], spento);//1sxdr      (verde 2)
    digitalWrite(semaforo2[5], spento);//2dx        (rosso 1)
    digitalWrite(semaforo2[2], spento);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], spento);//3dxdr      (rosso 2)
    digitalWrite(semaforo3[2], spento);//3sx        (rosso 1)
    digitalWrite(semaforo4[0], spento);//4dxdr      (rosso 1)
    digitalWrite(semaforo4[3], spento);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], spento);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[1], spento);//2p         (verde, buzzer attivo)
    digitalWrite(pedoni5_6[0], spento);//3p         (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[0], spento);//4p         (rosso, buzzer non attivo)
}

void finePedone3()
{
    digitalWrite(semaforo1[4], spento);//1dx        (verde 1)
    digitalWrite(semaforo1[2], spento);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[5], spento);//2dx        (rosso 1)
    digitalWrite(semaforo2[2], spento);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[3], spento);//3dxdr      (rosso 2)
    digitalWrite(semaforo3[0], spento);//3sx        (rosso 1)
    digitalWrite(semaforo4[1], spento);//4dxdr      (verde 1)
    digitalWrite(semaforo4[3], spento);//4sx        (rosso 2)

    digitalWrite(pedoni1_2[0], spento);//1p         (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], spento);//2p         (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[1], spento);//3p         (verde, buzzer attivo)
    digitalWrite(pedoni7_8[0], spento);//4p         (rosso, buzzer non attivo)
}

void finePedone4()
{
    digitalWrite(semaforo1[4], spento);//1dx        (verde 1)
    digitalWrite(semaforo1[2], spento);//1sxdr      (rosso 2)
    digitalWrite(semaforo2[1], spento);//2dx        (verde 1)
    digitalWrite(semaforo2[2], spento);//2sxdr      (rosso 2)
    digitalWrite(semaforo3[0], spento);//3dxdr       (nulla 1, rosso 1)
    digitalWrite(semaforo3[4], spento);//3sx         (verde 2)
    digitalWrite(semaforo4[0], spento);//4dxdr       (rosso 1)
    digitalWrite(semaforo4[3], spento);//4sx         (rosso 2)

    digitalWrite(pedoni1_2[0], spento);//1p          (rosso, buzzer non attivo)
    digitalWrite(pedoni3_4[0], spento);//2p          (rosso, buzzer non attivo)
    digitalWrite(pedoni5_6[0], spento);//3p          (rosso, buzzer non attivo)
    digitalWrite(pedoni7_8[1], spento);//4p          (verde, buzzer attivo)
}


//legge stato pulsanti
int letturaPulasanti()
{
    //bool premuto = false;

    for (int i = 0; i < 4; i++)
    {
        statobottone[i] = digitalRead(bottone[i]);
        if (statobottone[i] == 1)
        {
            return i;
        }
    }
    return -1;    
}

void alternaPiezo() // funzione beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep beep
{
    for (int i = 0; i < 10; i++)
    {
        tone(piezo, 10);
        delay(500);
        noTone(piezo);
        delay(500);
    }
}
