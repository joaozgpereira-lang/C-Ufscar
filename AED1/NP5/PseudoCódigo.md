Inteiro PosicaoNoConjunto (parâmetro por referência L do tipo Lista, parâmetro X do tipo Char) {
    
    Variável ElementoAtual do tipo Char;
    Variável TemElemento do tipo Boolean;
    Variável Contador do tipo Inteiro;
    
    Contador = 1;
    PegaOPrimeiro(L, ElementoAtual, TemElemento);
    
    Enquanto (TemElemento == Verdadeiro) Faça {
        Se (ElementoAtual == X) Então {
            Retorne Contador;
        }
        
        Contador = Contador + 1;
        PegaOPróximo(L, ElementoAtual, TemElemento);
    }
    
    Retorne 0; // Elemento X não encontrado na Lista
}