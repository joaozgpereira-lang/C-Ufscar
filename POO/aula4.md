# Resumo de POO — Tópicos Avançados

Resumo de estudo baseado nas aulas de POO (C++), cobrindo:

1. Objetos e membros `const`
2. Gerenciamento dinâmico de memória (`new` e `delete`)
3. Membros `static`
4. O ponteiro `this`

---

## 1. Objetos e membros `const`

### O que é um objeto?

Um objeto é uma **instância de uma classe**. Ele guarda **estado** (atributos) e oferece **comportamento** (métodos).

```cpp
class Aluno {
    private:
    int RA;
    string Nome;

    public:
    string GetNome() const;   // método const
    int GetRA() const;        // método const
    void SetNome(string Nome); // método normal (modifica o objeto)
};
```

### Métodos `const`

Um **método `const`** é aquele que promete **não modificar o objeto**. A palavra `const` vem depois da lista de parâmetros, antes do corpo:

```cpp
string Aluno::GetNome() const {
    // return Nome; — permitido: apenas leitura
    // Nome = "outro"; — ERRO de compilação: não pode modificar
    return Nome;
}
```

Regras importantes:

- Métodos `const` só podem **ler** atributos, nunca escrevê-los.
- Dentro de um método `const`, só é possível chamar outros métodos `const`.
- Métodos `const` podem ser chamados em objetos **`const`** ou normais.
- Métodos não-`const` **não podem** ser chamados em objetos `const`.

```cpp
const Aluno alunoConst("Maria");   // objeto const
alunoConst.GetNome();              // OK: GetNome() é const
alunoConst.SetNome("João");        // ERRO: SetNome() não é const
```

### `const` em outros lugares

```cpp
void exibir(const Aluno& a);       // parâmetro const (não será modificado)
const int VALOR_MAX = 100;         // constante
```

> **Por que usar?** O `const` documenta a intenção do código, evita modificações acidentais e permite que o compilador otimize melhor o programa.

---

## 2. Gerenciamento dinâmico de memória — `new` e `delete`

### Memória na pilha (stack) vs. heap

| | Pilha (stack) | Heap (dinâmica) |
|---|---|---|
| Alocação | Automática (ao criar a variável) | Manual, com `new` |
| Liberação | Automática (fim do escopo) | Manual, com `delete` |
| Tamanho | Fixo, definido em tempo de compilação | Definido em tempo de execução |

Quando não sabemos de antemão quantos objetos vamos precisar (ex.: quantidade informada pelo usuário), usamos alocação **dinâmica**.

### `new` — aloca no heap

```cpp
int* p = new int;          // aloca um int e guarda o endereço
*p = 42;                   // usa o espaço alocado

Aluno* aluno = new Aluno("Renato");  // aloca objeto, chama o construtor
```

Para **arrays**:

```cpp
int* vetor = new int[10];       // array de 10 ints
Aluno* turma = new Aluno[30];   // array de 30 Alunos
```

### `delete` — libera no heap

```cpp
delete p;              // libera o int
delete aluno;          // libera o objeto (chama o destrutor!)

delete[] vetor;        // libera ARRAYS com delete[]
delete[] turma;        // sempre use [] quando alocou com []
```

> **Regra de ouro:** quem aloca com `new` usa `delete`; quem aloca com `new[...]` usa `delete[]`. Misturar é comportamento indefinido.

### Problemas comuns

- **Memory leak (vazamento de memória):** aloca com `new` e esquece do `delete` — a memória nunca é liberada.
- **`delete` duplo:** liberar duas vezes o mesmo ponteiro → erro.
- **Ponteiro solto (dangling):** usar o ponteiro depois do `delete`.

```cpp
Aluno* a = new Aluno("Ana");
delete a;          // OK
// delete a;       // ERRO: delete duplo!
// a->GetNome();   // ERRO: a é dangling pointer
a = nullptr;       // boa prática: anular depois de deletar
```

### Exemplo completo

```cpp
#include <iostream>
using namespace std;

class Aluno {
    private:
    string Nome;

    public:
    Aluno(string n) { Nome = n; }
    ~Aluno() { cout << "Destruindo " << Nome << endl; }
    string GetNome() const { return Nome; }
};

int main() {
    // Alocado na pilha: destruído sozinho no fim do main
    Aluno estatico("João");

    // Alocado no heap: precisa de delete manual
    Aluno* dinamico = new Aluno("Maria");
    cout << dinamico->GetNome() << endl;

    delete dinamico;   // chama o destrutor e libera a memória

    // Se você esquecer o delete acima -> memory leak
    return 0;
}
```

Saída esperada:

```
Maria
Destruindo Maria
Destruindo João
```

---

## 3. Membros `static`

### Atributo `static`

Um **atributo `static`** pertence à **classe**, não a cada objeto. Ele é **compartilhado por todas as instâncias**: só existe **uma única cópia** na memória.

```cpp
class Aluno {
    private:
    int RA;
    static int contador;   // todos os Alunos compartilham esta variável

    public:
    Aluno() { RA = contador; contador++; }
    static int GetContador();
};

// OBRIGATÓRIO: inicializar o atributo static fora da classe
int Aluno::contador = 2000;
```

Regras:

- A **inicialização acontece fora da classe**: `tipo Classe::atributo = valor;`
- No construtor, cada objeto **incrementa o contador** — assim todos os RA saem únicos e sequenciais.
- O valor fica na classe, e não em cada cópia do objeto.

### Método `static`

Um **método `static`** pode ser chamado **sem criar um objeto**:

```cpp
int Aluno::GetContador() {
    return contador;
}

int main() {
    cout << Aluno::GetContador() << endl;  // chamado pelo nome da classe!
    return 0;
}
```

Regras:

- Método `static` **não tem `this`** (não há um objeto "atual").
- Só pode acessar outros membros `static` (ou passar objetos por parâmetro).

### Exemplo completo (como na aula)

```cpp
#include <iostream>
using namespace std;

class Aluno {
    private:
    int RA;
    string Nome;
    static int contador;

    public:
    Aluno(string n) {
        RA = contador;      // assume o valor atual do contador
        Nome = n;
        contador++;         // próximo aluno terá RA maior
    }
    int GetRA() const { return RA; }
    string GetNome() const { return Nome; }
    static int GetContador() { return contador; }
};

int Aluno::contador = 2000;   // inicialização fora da classe

int main() {
    Aluno A1("Renato");
    Aluno A2("Sílvio");
    Aluno A3("Enrique");

    cout << A1.GetRA() << ": " << A1.GetNome() << endl;
    cout << A2.GetRA() << ": " << A2.GetNome() << endl;
    cout << A3.GetRA() << ": " << A3.GetNome() << endl;

    // Método static chamado sem objeto
    cout << "Total de alunos: " << Aluno::GetContador() << endl;

    return 0;
}
```

Saída esperada:

```
2000: Renato
2001: Sílvio
2002: Enrique
Total de alunos: 2003
```

---

## 4. O ponteiro `this`

### O que é?

`this` é um **ponteiro implícito** que existe dentro de todo método não-`static`: ele aponta para o **próprio objeto** que chamou o método.

```cpp
void Aluno::SetNome(string Nome) {
    this->Nome = Nome;   // this->Nome é o atributo; Nome é o parâmetro
}
```

### Principal uso: desambiguação

Quando o parâmetro tem o **mesmo nome** do atributo, `this->` deixa explícito de qual estamos falando:

```cpp
void Aluno::SetNome(string Nome) {
    this->Nome = Nome;   // atributo  = parâmetro
}
```

Sem o `this`, `Nome = Nome;` atribuiria o parâmetro a ele mesmo, sem efeito nenhum!

### Outro uso: encadeamento de chamadas

Retornando `*this` (o objeto em si, desreferenciado do ponteiro), dá para **encadear** chamadas:

```cpp
class Retangulo {
    private:
    int largura = 0, altura = 0;

    public:
    Retangulo& setLargura(int l) { largura = l; return *this; }
    Retangulo& setAltura(int a)   { altura = a;   return *this; }
    int area() const { return largura * altura; }
};

int main() {
    Retangulo r;
    r.setLargura(5).setAltura(3);   // encadeamento!
    cout << r.area() << endl;       // 15
    return 0;
}
```

### Regras importantes

- `this` **não existe** em métodos `static` (não há objeto atual).
- `this` é um ponteiro: usa-se `this->membro` para acessar, e `*this` para obter o objeto.
- `this` pode ser usado em métodos `const`, mas aí ele é um ponteiro para objeto `const` (não dá para modificar).

---

## Resumo rápido

|     Tópico       |            Ideia principal        |                     Sintaxe/chave                      |
|------------------|-----------------------------------|--------------------------------------------------------|
| Membros `const`  | Método que não modifica o objeto  | `int GetRA() const;`                                   |
| `new` / `delete` | Alocação/liberação manual no heap | `new`, `delete`, `delete[]`                            |
| Membros `static` | Pertencem à classe, não ao objeto | `static int contador;` + `int Aluno::contador = 2000;` |
| Ponteiro `this`  | Ponteiro para o próprio objeto    | `this->atributo`, `return *this;`                      |

> Dica de estudo: use os exemplos acima num compilador (ex.: [cpp.sh](https://cpp.sh) ou VS Code) e tente **quebrá-los de propósito** — remover o `const`, esquecer o `delete`, tirar a inicialização do `static`, ver o que acontece. Errar de propósito é o melhor jeito de entender cada conceito.