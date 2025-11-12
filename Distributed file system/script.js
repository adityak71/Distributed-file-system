// ======= Node Class Simulation =======
class Node {
  constructor(name) {
    this.name = name;
    this.active = true;
    this.files = {};
  }

  storeFile(filename, data) {
    if (this.active) {
      this.files[filename] = data;
      log(`✅ ${this.name} stored '${filename}'`);
    } else {
      log(`⚠️ ${this.name} is DOWN. Cannot store file.`);
    }
  }

  hasFile(filename) {
    return this.files.hasOwnProperty(filename);
  }

  getFile(filename) {
    return this.active && this.hasFile(filename) ? this.files[filename] : "";
  }
}

// ======= Distributed File System =======
class DistributedFileSystem {
  constructor(totalNodes, replication) {
    this.nodes = [];
    this.replicationFactor = replication;
    for (let i = 1; i <= totalNodes; i++) {
      this.nodes.push(new Node(`Node_${i}`));
    }
    this.updateUI();
  }

  uploadFile(filename, data) {
    log(`📤 Uploading file: ${filename}`);
    let stored = 0;
    for (let node of this.nodes) {
      if (node.active) {
        node.storeFile(filename, data);
        stored++;
        if (stored >= this.replicationFactor) break;
      }
    }
    if (stored < this.replicationFactor)
      log(`⚠️ Not enough active nodes for full replication.`);
    this.updateUI();
  }

  downloadFile(filename) {
    log(`📥 Downloading '${filename}'...`);
    for (let node of this.nodes) {
      if (node.active && node.hasFile(filename)) {
        log(`✅ File retrieved from ${node.name}: "${node.getFile(filename)}"`);
        return;
      }
    }
    log(`❌ File not available (replicas lost or nodes down).`);
  }

  failNode(index) {
    let node = this.nodes[index];
    if (node && node.active) {
      node.active = false;
      log(`💀 ${node.name} has FAILED.`);
    } else {
      log(`⚠️ Node already down or invalid.`);
    }
    this.updateUI();
  }

  recoverNode(index) {
    let node = this.nodes[index];
    if (node && !node.active) {
      node.active = true;
      log(`🔄 ${node.name} is RECOVERED.`);
    } else {
      log(`⚠️ Node already active or invalid.`);
    }
    this.updateUI();
  }

  repairFaults() {
    log(`🔧 Repairing Faults...`);
    let fileCount = {};

    // Count files in active nodes
    for (let node of this.nodes) {
      if (!node.active) continue;
      for (let file in node.files) {
        fileCount[file] = (fileCount[file] || 0) + 1;
      }
    }

    // Re-replicate missing files
    for (let filename in fileCount) {
      let copies = fileCount[filename];
      if (copies < this.replicationFactor) {
        log(`♻️ Re-replicating '${filename}' (${copies}/${this.replicationFactor})`);
        let data = "";
        for (let node of this.nodes) {
          if (node.active && node.hasFile(filename)) {
            data = node.getFile(filename);
            break;
          }
        }
        for (let node of this.nodes) {
          if (copies >= this.replicationFactor) break;
          if (node.active && !node.hasFile(filename)) {
            node.storeFile(filename, data);
            copies++;
          }
        }
      }
    }

    log(`✅ Fault repair completed.`);
    this.updateUI();
  }

  listFiles() {
    log(`📂 Listing file distribution:`);
    for (let node of this.nodes) {
      log(`${node.name} (${node.active ? "Active" : "Down"}): ${
        Object.keys(node.files).length ? Object.keys(node.files).join(", ") : "[Empty]"
      }`);
    }
  }

  updateUI() {
    const display = document.getElementById("nodeDisplay");
    display.innerHTML = "";
    this.nodes.forEach((node) => {
      const div = document.createElement("div");
      div.className = `node ${node.active ? "" : "down"}`;
      div.innerHTML = `
        <h3>${node.name}</h3>
        <p>Status: ${node.active ? "🟢 Active" : "🔴 Down"}</p>
        <p>Files: ${Object.keys(node.files).length ? Object.keys(node.files).join(", ") : "Empty"}</p>
      `;
      display.appendChild(div);
    });
  }
}

// ======= UI Logic =======
const dfs = new DistributedFileSystem(4, 2);
const output = document.getElementById("output");

function log(msg) {
  output.innerHTML += msg + "<br/>";
  output.scrollTop = output.scrollHeight;
}

function uploadFile() {
  const filename = document.getElementById("filename").value.trim();
  const data = document.getElementById("data").value.trim();
  if (!filename || !data) return log("⚠️ Enter filename and data.");
  dfs.uploadFile(filename, data);
}

function downloadFile() {
  const filename = document.getElementById("filename").value.trim();
  if (!filename) return log("⚠️ Enter filename to download.");
  dfs.downloadFile(filename);
}

function listFiles() {
  dfs.listFiles();
}

function failNode() {
  const n = parseInt(document.getElementById("nodeNum").value);
  if (!n) return log("⚠️ Enter valid node number.");
  dfs.failNode(n - 1);
}

function recoverNode() {
  const n = parseInt(document.getElementById("nodeNum").value);
  if (!n) return log("⚠️ Enter valid node number.");
  dfs.recoverNode(n - 1);
}

function repairFaults() {
  dfs.repairFaults();
}
