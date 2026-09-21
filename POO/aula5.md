# Resumo de POO — Cópia de Objetos e Passagem por Referência

Resumo de estudo baseado nas aulas de POO (C++), cobrindo:

1. Cópia de classe (cópia padrão / rasa)
2. Construtor de cópia
3. Construtor de cópia quando a classe usa **ponteiros** (cópia profunda)
4. Passagem por valor, por referência e por referência `const`
5. A **Regra dos Três** (destrutor + construtor de cópia + `operator=`)

---

## 1. Cópia de classe (cópia padrão / rasa)

Quando você escreve

```cpp
Aluno B = A;   // ou: Aluno B(A);
```

o compilador precisa criar `B` a partir de `A`. Se você **não** escreveu nada
especial, o compilador gera automaticamente um **construtor de cópia implícito**,
que faz uma **cópia membro a membro** (um atributo de cada vez).

```cpp
class Aluno {
    private:
    int RA;
    string Nome;
};

Aluno A("Renato");
Aluno B = A;   // compilador copia RA e Nome, um por um
```

Para atributos simples (`int`, `string`, `double`…), isso **funciona perfeitamente**:
cada objeto passa a ter seus próprios valores.

> **O problema aparece quando a classe tem um ponteiro.** Copiar o ponteiro copia
> só o **endereço**, não o conteúdo apontado. Os dois objetos passam a apontar
> para **a mesma memória** — isso é a chamada **cópia rasa (shallow copy)**.

```cpp
class Vetor {
    private:
    int* dados;     // ponteiro para memória alocada no heap
    int tamanho;
};
```

Com a cópia rasa:

```
A.dados ──┐
          └──► [ mesmos dados no heap ]
B.dados ──┘
```

Consequências ruins:

- Alterar `B` **também altera** `A` (eles compartilham os dados).
- Ao sair de escopo, **os dois destrutores** fazem `delete[]` no **mesmo** ponteiro
  → **double free** (liberação dupla) = comportamento indefinido / travamento.

É exatamente por isso que a classe precisa de um **construtor de cópia próprio**.

---

## 2. Construtor de cópia

### Sintaxe

```cpp
Classe(const Classe& outra);
```

Exemplo:

```cpp
Aluno::Aluno(const Aluno& outro) {
    RA   = outro.RA;
    Nome = outro.Nome;
}
```

Detalhes importantes:

- O parâmetro é uma **referência** (`&`). Se fosse **por valor** (`Aluno outro`),
  para copiar o argumento o compilador precisaria... chamar o construtor de cópia,
  que precisaria copiar de novo, infinitamente. Por isso a referência é obrigatória.
- É `const` porque **não queremos modificar o objeto de origem**.
- Não tem retorno.

### Quando o construtor de cópia é chamado?

| Situação | Exemplo | Chama o construtor de cópia? |
|---|---|---|
| Inicialização direta | `Vetor B(A);` | **Sim** |
| Inicialização com `=` | `Vetor B = A;` | **Sim** (parece atribuição, mas é cópia!) |
| Passagem **por valor** para função | `void f(Vetor v); f(A);` | **Sim** |
| Retorno **por valor** | `return A;` | **Sim** (o compilador pode otimizar com RVO) |
| Atribuição em objeto que já existe | `Vetor B; B = A;` | **Não** — chama o `operator=` (seção 5) |
| Passagem por **referência** | `void f(Vetor& v);` | **Não** |

> **Cuidado com a pegadinha:** `Vetor B = A;` **não** é atribuição, é **cópia**
> (o objeto `B` está sendo criado agora). Já `B = A;` (com `B` já existindo) é
> atribuição.

---

## 3. Construtor de cópia quando a classe usa ponteiros — cópia profunda

Para o caso do `Vetor` com `int* dados`, a cópia precisa ser **profunda (deep copy)**:
alocar **memória nova** para o novo objeto e copiar os **valores**.

```cpp
Vetor::Vetor(const Vetor& outro) {
    tamanho = outro.tamanho;
    dados = new int[tamanho];              // 1) aloca memória NOVA
    for (int i = 0; i < tamanho; i++)      // 2) copia os VALORES
        dados[i] = outro.dados[i];
}
```

Agora cada objeto tem **o seu próprio** array:

```
A.dados ──► [ 1  3  5 ]
B.dados ──► [ 1  3  5 ]   (bloco diferente, valores copiados)
```

### Rasa x profunda, lado a lado

| | Cópia rasa (padrão) | Cópia profunda (manual) |
|---|---|---|
| O que o ponteiro copia | o **endereço** | aloca novo bloco e copia os **valores** |
| Objetos compartilham dados? | **Sim** | **Não** |
| `delete[]` duplo no destrutor? | **Sim (erro!)** | Não |
| Quando usar | classes sem ponteiros | classes com `new`/ponteiro |

### Memória e destrutor

Lembre que quem aloca com `new[]` libera com `delete[]`:

```cpp
Vetor::~Vetor() {
    delete[] dados;   // cada objeto libera o SEU bloco
}
```

Com a cópia profunda, cada objeto tem o seu bloco → cada destrutor libera o seu →
**sem double free**.

---

## 4. Passagem por referência

### Por valor

```cpp
void PorValor(Vetor v) {   // cria uma CÓPIA de v
    v.Set(0, -1);          // altera só a cópia local
}
```

- Copia o objeto inteiro (chama o **construtor de cópia**).
- Custa tempo/memória em objetos grandes.
- Se a classe tiver ponteiro sem construtor de cópia → dispara o bug da cópia rasa.
- Modificações **não** afetam o original.

### Por referência

```cpp
void PorReferencia(Vetor& v) {   // v é um "apelido" para o objeto original
    v.Set(0, -2);                // altera o ORIGINAL
}
```

- **Não copia** nada (não chama o construtor de cópia).
- Modificações **afetam** o objeto original.
- Uma referência **não pode ser nula** e precisa ser inicializada.

### Por referência `const` (o mais usado para ler)

```cpp
void Mostrar(const Vetor& v) {   // sem cópia E sem risco de alterar
    // v.Set(0, 0);   // ERRO de compilação: v é const
    cout << v.GetTamanho() << endl;
}
```

- **Não copia** (rápido) e **não deixa modificar** (seguro).
- É a escolha padrão para parâmetros grandes que só serão lidos.

### Comparação rápida

| Forma | Copia? | Pode modificar o original? | Pode ser nulo? |
|---|---|---|---|
| `void f(T x)` | **Sim** | Não | Não |
| `void f(T& x)` | Não | **Sim** | Não |
| `void f(const T& x)` | Não | Não | Não |
| `void f(T* x)` | Não | **Sim** (via `*x`/`x->`) | **Sim** (`nullptr`) |

> **Regra prática:** leitura de objetos grandes → `const T&`;
> precisa modificar o original → `T&`; pode não existir → `T*`.

---

## 5. A Regra dos Três

> Se uma classe precisa de **um** destes três, provavelmente precisa dos **três**:
> **destrutor**, **construtor de cópia** e **operador de atribuição (`operator=`)**.

O `operator=` é o irmão do construtor de cópia: ele é usado quando o objeto
**já existe** e vai receber os valores de outro.

```cpp
Vetor& Vetor::operator=(const Vetor& outro) {
    if (this == &outro) return *this;   // 1) evita auto-atribuição (a = a)
    delete[] dados;                     // 2) libera a memória antiga
    tamanho = outro.tamanho;
    dados = new int[tamanho];           // 3) aloca nova
    for (int i = 0; i < tamanho; i++)   // 4) copia os valores
        dados[i] = outro.dados[i];
    return *this;                       // 5) permite encadear a = b = c
}
```

Pontos de atenção:

- Sem o teste `if (this == &outro)`, fazer `v = v;` apagaria os próprios dados
  e copiaria lixo.
- É preciso **liberar a memória antiga** antes de alocar a nova, senão há vazamento.
- Retorna `Vetor&` (`*this`) para permitir encadeamento.

---

## 6. Exemplo completo (classe `Vetor` com alocação dinâmica)

```cpp
#include <iostream>
using namespace std;

class Vetor {
    private:
    int* dados;
    int tamanho;

    public:
    Vetor(int tam);
    Vetor(const Vetor& outro);              // construtor de cópia
    ~Vetor();                               // destrutor
    Vetor& operator=(const Vetor& outro);   // atribuição

    void Set(int indice, int valor);
    int  Get(int indice) const;
    int  GetTamanho() const;
};

Vetor::Vetor(int tam) {
    tamanho = tam;
    dados = new int[tamanho];
    for (int i = 0; i < tamanho; i++) dados[i] = 0;
    cout << "Construtor comum: alocou " << tamanho << " posicoes\n";
}

// Cópia PROFUNDA: memória nova + valores copiados
Vetor::Vetor(const Vetor& outro) {
    tamanho = outro.tamanho;
    dados = new int[tamanho];
    for (int i = 0; i < tamanho; i++) dados[i] = outro.dados[i];
    cout << "Construtor de copia: copiou " << tamanho << " posicoes\n";
}

Vetor::~Vetor() {
    delete[] dados;
    cout << "Destrutor: liberou " << tamanho << " posicoes\n";
}

Vetor& Vetor::operator=(const Vetor& outro) {
    cout << "Operador de atribuicao\n";
    if (this == &outro) return *this;   // auto-atribuicao
    delete[] dados;                     // libera o bloco antigo
    tamanho = outro.tamanho;
    dados = new int[tamanho];
    for (int i = 0; i < tamanho; i++) dados[i] = outro.dados[i];
    return *this;
}

void Vetor::Set(int indice, int valor) { dados[indice] = valor; }
int  Vetor::Get(int indice) const { return dados[indice]; }
int  Vetor::GetTamanho() const { return tamanho; }

// --- Passagens ---
void PorValor(Vetor v) {          // COPIA: não afeta o original
    v.Set(0, -1);
    cout << "Alterei so a copia local: v[0] = " << v.Get(0) << endl;
}

void PorReferencia(Vetor& v) {    // sem copia: altera o original
    v.Set(0, -2);
}

void PorReferenciaConst(const Vetor& v) {   // sem copia e sem alterar
    // v.Set(0, 0);   // ERRO: v e const
    cout << "Leitura por const&: tamanho = " << v.GetTamanho() << endl;
}

int main() {
    Vetor impar(3);
    impar.Set(0, 1);
    impar.Set(1, 3);
    impar.Set(2, 5);

    cout << "\n>> Vetor copia1(impar);   // inicializacao direta\n";
    Vetor copia1(impar);              // construtor de copia

    cout << "\n>> Vetor copia2 = impar;  // inicializacao com '='\n";
    Vetor copia2 = impar;             // TAMBEM construtor de copia

    cout << "\n>> Vetor copia3(3); copia3 = impar;  // atribuicao\n";
    Vetor copia3(3);
    copia3 = impar;                   // operator=

    cout << "\n>> Alterando copia1[0] = 99 (nao afeta o original)\n";
    copia1.Set(0, 99);
    cout << "impar[0]  = " << impar.Get(0)  << endl;   // 1
    cout << "copia1[0] = " << copia1.Get(0) << endl;   // 99

    cout << "\n>> Passagem por valor\n";
    PorValor(impar);                  // dispara o construtor de copia
    cout << "impar[0] apos PorValor = " << impar.Get(0) << endl;   // 1

    cout << "\n>> Passagem por referencia\n";
    PorReferencia(impar);
    cout << "impar[0] apos PorReferencia = " << impar.Get(0) << endl; // -2

    cout << "\n>> Leitura por const&\n";
    PorReferenciaConst(impar);

    cout << "\n>> Fim do main (destrutores na ordem inversa)\n";
    return 0;
}
```

Saída esperada:

```
Construtor comum: alocou 3 posicoes

>> Vetor copia1(impar);   // inicializacao direta
Construtor de copia: copiou 3 posicoes

>> Vetor copia2 = impar;  // inicializacao com '='
Construtor de copia: copiou 3 posicoes

>> Vetor copia3(3); copia3 = impar;  // atribuicao
Construtor comum: alocou 3 posicoes
Operador de atribuicao

>> Alterando copia1[0] = 99 (nao afeta o original)
impar[0]  = 1
copia1[0] = 99

>> Passagem por valor
Construtor de copia: copiou 3 posicoes
Alterei so a copia local: v[0] = -1
Destrutor: liberou 3 posicoes
impar[0] apos PorValor = 1

>> Passagem por referencia
impar[0] apos PorReferencia = -2

>> Leitura por const&
Leitura por const&: tamanho = 3

>> Fim do main (destrutores na ordem inversa)
Destrutor: liberou 3 posicoes
Destrutor: liberou 3 posicoes
Destrutor: liberou 3 posicoes
Destrutor: liberou 3 posicoes
```

Observe:

- `copia2 = impar` (criando o objeto) chamou o **construtor de cópia**, não o `operator=`.
- `copia3 = impar` (objeto já existente) chamou o **`operator=`**.
- `PorValor` criou e destruiu **uma cópia**; `PorReferencia` não copiou nada.
- No fim, os 4 objetos vivos são destruídos na **ordem inversa** da criação,
  cada um liberando **o seu próprio** bloco → sem double free.

---

## Resumo rápido

| Tópico | Ideia principal | Sintaxe/chave |
|---|---|---|
| Cópia padrão | Membro a membro; **rasa** se houver ponteiro | gerada pelo compilador |
| Construtor de cópia | Cria um novo objeto a partir de outro | `Vetor(const Vetor& outro);` |
| Cópia profunda | Aloca memória nova e copia os valores | `dados = new int[tamanho];` + laço de cópia |
| Por valor | **Copia** o objeto (dispara o construtor de cópia) | `void f(Vetor v)` |
| Por referência | **Não copia**, altera o original | `void f(Vetor& v)` |
| Por `const&` | Não copia e não altera (ideal p/ leitura) | `void f(const Vetor& v)` |
| Regra dos Três | Destrutor + cópia + atribuição andam juntos | `~Vetor()`, `Vetor(const Vetor&)`, `operator=` |

> Dica de estudo: compile o exemplo acima, mas **apague o construtor de cópia** e
> veja o programa quebrar (double free / dados compartilhados). Depois **apague o
> destrutor** e observe o vazamento. Sentir o erro é o melhor jeito de entender
> por que cada um dos três existe.
