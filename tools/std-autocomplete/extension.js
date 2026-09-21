// std:: Autocomplete
// Completa nomes da std:: de forma inteligente por arquivo:
//   - Sem "using namespace std;" : "cout" + Tab -> "std::cout"
//   - Com  "using namespace std;" : "cout" + Tab -> "cout" (não muda)
const vscode = require('vscode');

const STD_SYMBOLS = {
  cout: 'std::cout',
  cin: 'std::cin',
  cerr: 'std::cerr',
  clog: 'std::clog',
  endl: 'std::endl',
  string: 'std::string',
  vector: 'std::vector',
  array: 'std::array',
  map: 'std::map',
  set: 'std::set',
  pair: 'std::pair',
  list: 'std::list',
  stack: 'std::stack',
  queue: 'std::queue',
};

function activate(context) {
  const provider = vscode.languages.registerCompletionItemProvider(
    [{ language: 'cpp' }, { language: 'c' }],
    {
      provideCompletionItems(document, position) {
        const linePrefix = document.lineAt(position).text.slice(0, position.character);

        // Não completar dentro de comentários de linha (//)
        const commentIdx = linePrefix.indexOf('//');
        const m = /([A-Za-z_][A-Za-z0-9_]*)$/.exec(linePrefix);
        if (commentIdx !== -1 && (!m || m.index > commentIdx)) {
          return undefined; // está dentro de //xxx
        }

        if (!m) {
          return undefined;
        }

        const typed = m[1];
        const usesUsingNamespace = /using[ \t]+namespace[ \t]+std[ \t]*;/.test(
          document.getText()
        );

        const range = new vscode.Range(
          position.translate({ characterDelta: -typed.length }),
          position
        );

        const items = [];
        for (const name of Object.keys(STD_SYMBOLS)) {
          if (!name.startsWith(typed)) continue;
          const insert = usesUsingNamespace ? name : STD_SYMBOLS[name];
          const item = new vscode.CompletionItem(
            insert,
            vscode.CompletionItemKind.Module
          );
          item.insertText = insert;
          item.range = range;
          item.filterText = name;
          item.sortText = '0' + name; // ficar no topo da lista
          item.detail = usesUsingNamespace ? 'iostream/containers' : 'std';
          items.push(item);
        }
        return items;
      },
    }
  );

  context.subscriptions.push(provider);
}

function deactivate() {}

module.exports = { activate, deactivate };