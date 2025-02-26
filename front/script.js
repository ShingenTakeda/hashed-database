const controleDeTela = [
  {
    acao: "select-id",
    endpoint: "btnSelect"
  },
];

//TODO: REVER A NECESSIDADE
// {
//   acao: "insert-id",
//   endpoint: "btnInsert"
// },
// {
//   acao: "insert-name",
//   endpoint: "btnInsert"
// },
// {
//   acao: "delete-id",
//   endpoint: "btnDelete"
// },
// {
//   acao: "update-id",
//   endpoint: "btnUpdate"
// },
// {
//   acao: "update-name",
//   endpoint: "btnUpdate"
// },

controleDeTela.forEach(obj => {
  document.getElementById(obj.acao).addEventListener('keyup', key => {
    if (key.code === "Enter") {
      document.getElementById(obj.endpoint).click()
    }
  })
});

function validarChave(obj) {
  if(obj.value == "") {
    alert("A Chave de busca não pode estar vazia, por favor digite uma palavra em inglês qualquer...");
    return true;
  }

  if(obj.value.indexOf(' ') >= 0) {
    alert("Tente escrever somente uma palavra ou remova o espaço em branco");
    return true;
  }

  return false;
}

function showTab(tabId) {
  document.querySelectorAll(".tab-content").forEach((tab) => {
    tab.style.display = "none";
  });
  document.getElementById(tabId).style.display = "block";
}

async function loadData() {
  const chave = document.getElementById("select-id");

  if(validarChave(chave)) return;

  const id = chave.value.trim();
  // const response = await fetch(`https://api.mitsu/hashedDatabase/select/${id}`, {
  //   method: "GET",
  // });
  // const data = await response.json();
  // document.getElementById("result-list").innerHTML = `<li>${data.name}</li>`;


  //Mock pra visualizacao da lista com mais de um elemento ou so um...
  dataLength = [{ name: "Joaozinho da Silva" }, { name: "Carlos da Cunha" }];
  dataNoLength = { name: "Joaozinho da Silva" };

  mocks = [dataLength, dataNoLength];

  choice = Math.round(Math.random());

  if (mocks[choice].length != null) {
    document.getElementById("result-list").innerHTML = dataLength
      .map((d) => {
        return `<li>${d.name}</li>`;
      })
      .join("");
  } else {
    document.getElementById(
      "result-list"
    ).innerHTML = `<li>${dataNoLength.name}</li>`;
  }
}

async function insertData() {
  //   const id = document.getElementById("insert-id").value;
  //   const name = document.getElementById("insert-name").value;
  //   await fetch("https://api.mitsu/hashedDatabase", {
  //     method: "POST",
  //     headers: { "Content-Type": "application/json" },
  //     body: JSON.stringify({ id, name }),
  //   });
  //   alert("Inserido com sucesso!");
}

async function updateData() {
  //   const id = document.getElementById("update-id").value;
  //   const name = document.getElementById("update-name").value;
  //   await fetch(`https://api.mitsu/hashedDatabase/update/${id}`, {
  //     method: "PUT",
  //     headers: { "Content-Type": "application/json" },
  //     body: JSON.stringify({ name }),
  //   });
  //   alert("Atualizado com sucesso!");
}

async function deleteData() {
  //   const id = document.getElementById("delete-id").value;
  //   await fetch(`https://api.mitsu/hashedDatabase/delete/${id}`, {
  //     method: "DELETE",
  //   });
  //   alert("Deletado com sucesso!");
}
