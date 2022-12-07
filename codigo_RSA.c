
This site has been acquired by Toptal
(Attention! API endpoint has changed)
Save New Duplicate & Edit Just Text1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199
200
201
202
203
204
205
206
207
208
209
210
211
212
213
214
215
216
217
218
219
220
221
222
223
224
225
226
227
228
229
230
231
232
233
234
235
236
237
238
239
240
241
242
243
244
245
246
247
248
249
250
251
252
253
254
255
256
257
258
259
260
261
262
263
264
265
266
267
268
269
270

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

long long numero_primo(long long p){

    long long i;
    double j;

    // Calcula a raiz quadrada para p
    j = sqrt(p);

    for (i = 2; i <= j; i++){
        // Retorna 0 caso não seja um número primo
        if (p % i == 0)
            return 0;
    }

    // Retorna 1 quando é um número primo
    return 1;
}

int find(char letras[], char str[], int n, int j, int i){
    if (str[i] == letras[j]){
        return j;
    }
    else{
        j++;
        return find(letras, str, n, j, i);
    }
    return find(letras, str, n, j, i);
}

void cripto(char letras[], int tabela[], char str[], unsigned long int new[], int n, int i){
    if (i == n){
        return;
    }
    else{
        int pos;
        pos = find(letras, str, n, 0, i);
        new[i] = tabela[pos];
    }
    cripto(letras, tabela, str, new, n, i + 1);
}

// cálculo da forma reduzida de a^e módulo n, usando a expansão binária do expoente
long potencia(long long a, long long e, long long n){

    long long A = a, P = 1, E = e;

     while (1){

        if (E == 0)
            return P;

        else if (E % 2 != 0){

            P = (A * P) % n;
            E = (E - 1) / 2;
        }

        else{
            E = E / 2;
        }

        A = (A * A) % n;
    }
}

int associacao(int tabela[], long long new[], int n, int j, int i){
    if (new[i] == tabela[j]){
        return j;
    }
    else{
        j++;
        return associacao(tabela, new, n, j, i);
    }
    return associacao(tabela, new, n, j, i);
}

void decifrar(char letra[], int tabela[], long long new[], char crip[], int n, int i){
    if (i == n){
        crip[i] = '\0';
        return;
    }

    else{
        long pos;
        pos = associacao(tabela, new, n, 0, i);
        crip[i] = letra[pos];
    }

    decifrar(letra, tabela, new, crip, n, i + 1);
}

//mdc estendido que retorna d
//long long algoritmo_Extendido(long long a, long long b, int *x, int *y){
    //if (a == 0){
      //  *x = 0;
        //*y = 1;
        //return b;
    //}

    //int x1, y1;
    //int gcd = algoritmo_Extendido(b % a, a, &x1, &y1);
    //*x = y1 - (b / a) * x1;
    //*y = x1;

    //return gcd;
//}

void Gerador_de_Chaves(){
    FILE *chave_pul;
    FILE *chave_pri;
    long long int p, q, e, n, phi;
    system("clear");
    printf("-- Insira dois números primos e um expoente válido:\n");
    scanf("%lld %lld %lld", &p, &q, &e);

    while(!numero_primo(p) || !numero_primo(q) || !numero_primo(e)){
        system("clear");
        printf("-- Um dos números que você digitou é inválido. Insira dois números primos e um expoente válido:\n");
        scanf("%lld %lld %lld", &p, &q, &e);
    }
  
    
    n = p * q;
    phi = (p - 1) * (q - 1);

    int d = 0;

    while((d * e) % phi != 1)
    {
        d++;
    }

    chave_pul = fopen("chave_publica.txt", "w");
    chave_pri = fopen("chave_privada.txt", "w");
    fprintf(chave_pul , " Aqui está sua chave pública: n = {%lld} e = {%lld}", n, e);
    fprintf(chave_pri , " Aqui está sua chave privada: p = {%lld} q = {%lld} d = {%d}", p, q, d);
    fclose(chave_pul);
    fclose(chave_pri);
    system("clear");
    printf("-- As chaves foram criadas com sucesso! ");
    
}

void Encriptar(){
    system("clear");
    long long int e, n;
    FILE *destino;
    destino = fopen("Mensagem_encriptografada.txt", "w");
    char letras[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
    int tabela[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
    char str[999];

    printf("-- Insira a mensagem que deseja criptografar: \n");
    scanf(" %[^\n]", str);
    system("clear");
    printf("-- Insira a chave pública ('n' e 'e'): \n");
    scanf(" %lld %lld", &n, &e);
    system("clear");

    int tam = strlen(str);
    unsigned long int new[tam], crip[tam];
    unsigned long int val[tam];

    for (int i = 0; i < tam; i++){
        str[i] = tolower(str[i]);
    }
    cripto(letras, tabela, str, new, tam, 0);

    for (int i = 0; i < tam; i++){
        crip[i] = potencia(new[i], e, n);
    }

    for (int i = 0; i < tam; i++){
        fprintf(destino, "%lu ", crip[i]);
    }
    fclose(destino);
    printf("-- A criptografia foi concluída com sucesso! ");
}

void Desencriptar(){
    FILE *desencriptada;
    FILE *encriptada;

    long long value[999];
    
    char letras[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
    int  tabela[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
    
    encriptada = fopen("Mensagem_encriptografada.txt", "r");

    long long phi, e, p, q, n;
    int x, y;

    system("clear");
    printf("-- Insira a chave privada:\n");
    scanf("%lld %lld %lld", &p, &q, &e);
    system("clear");
    
    phi = (p - 1) * (q - 1);
    n = p * q;

    int d = 0, tam = 0, numero;

    while((d * e) % phi != 1)
    {
        d++;
    }

    while (fscanf(encriptada, "%lld", &value[tam]) != EOF){
        tam++;
    }

    long long new[tam];
    char crip[tam];

    for (int c = 0; c < tam; c++){
        new[c] = potencia(value[c], d, n);
    }

    desencriptada = fopen("Mensagem_desencriptografada.txt", "w");
    decifrar(letras, tabela, new, crip, tam, 0);

    fprintf(desencriptada, "%s", crip);
    printf("-- A descriptografia foi concluída com sucesso! ");

    fclose(desencriptada);
    fclose(encriptada);
}

int main(){
    int programa = 1;
    while (programa != 0){
        int tarefa;
        
        printf("\n\n 1. Gerar Chave Pública\t\t|CRIPTOGRAFIA RSA - MATEMÁTICA DISCRETA|\n 2. Encriptar Arquivo\n 3. Desencriptar Arquivo\n 4. Sair\n\n -- Insira a tarefa desejada : ");
        scanf("%d", &tarefa);

        while(tarefa != 1 && tarefa != 2 && tarefa != 3 && tarefa != 4){
            system("clear");
            printf("Opção inválida, escolha uma opção válida: \n\n 1. Gerar Chave Pública\n 2. Encriptar Arquivo\n 3. Desencriptar Arquivo\n 4. Sair\n\n -- ");
            scanf("%d", &tarefa);
        }

        switch(tarefa){
            case 1:
                Gerador_de_Chaves(); break;

            case 2:
                Encriptar();         break;

            case 3:
                Desencriptar();      break;
            
            case 4:
                system("clear");
                printf("Encerrando...\nObrigado! \n");
                programa = 0;
            break;
        }
    }

    return 0;
}