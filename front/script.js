function showTab(tabId) {
  document.querySelectorAll(".tab-content").forEach((tab) => {
    tab.style.display = "none";
  });
  document.getElementById(tabId).style.display = "block";
}

async function loadData() {
  //   const id = document.getElementById("select-id").value;
  //   const response = await fetch(`https://api.example.com/data/${id}`, {
  //     method: "GET",
  //   });
  //   const data = await response.json();
  //   document.getElementById("result-list").innerHTML = `<li>${data.name}</li>`;
}

async function insertData() {
  //   const id = document.getElementById("insert-id").value;
  //   const name = document.getElementById("insert-name").value;
  //   await fetch("https://api.example.com/data", {
  //     method: "POST",
  //     headers: { "Content-Type": "application/json" },
  //     body: JSON.stringify({ id, name }),
  //   });
  //   alert("Inserido com sucesso!");
}

async function updateData() {
  //   const id = document.getElementById("update-id").value;
  //   const name = document.getElementById("update-name").value;
  //   await fetch(`https://api.example.com/data/${id}`, {
  //     method: "PUT",
  //     headers: { "Content-Type": "application/json" },
  //     body: JSON.stringify({ name }),
  //   });
  //   alert("Atualizado com sucesso!");
}

async function deleteData() {
  //   const id = document.getElementById("delete-id").value;
  //   await fetch(`https://api.example.com/data/${id}`, {
  //     method: "DELETE",
  //   });
  //   alert("Deletado com sucesso!");
}
