Defina o tipo Node = Registro {
    Info do tipo Char,
    Next do tipo ponteiro para Node;
}
Defina o tipo NodePtr = ponteiro para Node;

Defina o tipo Pilha = Registro {
    Topo do tipo NodePtr;
}

Cria(parâmetro por referência P do tipo Pilha) {
    P.Topo = Null;
}

Boolean Vazia(parâmetro por referência P do tipo Pilha) {
    Se (P.Topo == Null)
        Então Retorne Verdadeiro;
    Senão Retorne Falso;
}

Boolean Cheia(parâmetro por referência P do tipo Pilha) {
    Retorne Falso;
}

Empilha(parâmetro por referência P do tipo Pilha, parâmetro X do tipo Char, parâmetro por referência DeuCerto do tipo Boolean) {
    Variável PAux do tipo NodePtr;
    Variável PFundo do tipo NodePtr;

    PAux = NewNode;
    DeuCerto = Verdadeiro;
    PAux->Info = X;

    Se (Vazia(P) == Verdadeiro) Então {
        P.Topo = PAux;
        PAux->Next = PAux;
    } Senão {
        PFundo = P.Topo;
        Enquanto (PFundo->Next != P.Topo) Faça {
            PFundo = PFundo->Next;
        }
        PAux->Next = P.Topo;
        P.Topo = PAux;
        PFundo->Next = P.Topo;
    }
}

Desempilha(parâmetro por referência P do tipo Pilha, parâmetro por referência X do tipo Char, parâmetro por referência DeuCerto do tipo Boolean) {
    Variável PAux do tipo NodePtr;
    Variável PFundo do tipo NodePtr;

    Se (Vazia(P) == Verdadeiro) Então {
        DeuCerto = Falso;
    } Senão {
        DeuCerto = Verdadeiro;
        X = P.Topo->Info;
        PAux = P.Topo;

        Se (P.Topo->Next == P.Topo) Então {
            P.Topo = Null;
        } Senão {
            PFundo = P.Topo;
            Enquanto (PFundo->Next != P.Topo) Faça {
                PFundo = PFundo->Next;
            }
            P.Topo = P.Topo->Next;
            PFundo->Next = P.Topo;
        }
        DeleteNode(PAux);
    }
}