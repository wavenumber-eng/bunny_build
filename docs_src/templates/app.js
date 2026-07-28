(function () {
  const themeButton = document.querySelector("[data-action='theme']");
  const fontButton = document.querySelector("[data-action='font']");
  const root = document.documentElement;
  const fonts = [
    ["consolas", "Consolas, Monaco, 'Courier New', monospace"],
    ["cascadia", "'Cascadia Code', 'Cascadia Mono', Consolas, monospace"],
    ["jetbrains", "'JetBrains Mono', Consolas, monospace"],
    ["ibm plex", "'IBM Plex Mono', Consolas, monospace"],
    ["courier", "'Courier New', Courier, monospace"],
  ];
  let fontIndex = 0;

  function setTheme(next) {
    root.dataset.theme = next;
    if (themeButton) themeButton.textContent = "theme: " + next;
    try {
      localStorage.setItem("ezh-theme", next);
    } catch (_) {}
  }

  function setFontIndex(next) {
    const index = ((next % fonts.length) + fonts.length) % fonts.length;
    fontIndex = index;
    root.style.setProperty("--mono", fonts[index][1]);
    if (fontButton) fontButton.textContent = "font: " + fonts[index][0];
    try {
      localStorage.setItem("ezh-font-index", String(index));
    } catch (_) {}
  }

  try {
    const savedTheme = localStorage.getItem("ezh-theme");
    const savedFont = localStorage.getItem("ezh-font-index");
    if (savedTheme) setTheme(savedTheme);
    if (savedFont) setFontIndex(parseInt(savedFont, 10) || 0);
  } catch (_) {}
  setTheme(root.dataset.theme || "dark");
  if (!root.style.getPropertyValue("--mono")) setFontIndex(0);

  if (themeButton) {
    themeButton.addEventListener("click", function () {
      setTheme(root.dataset.theme === "light" ? "dark" : "light");
    });
  }

  if (fontButton) {
    fontButton.addEventListener("click", function () {
      setFontIndex(fontIndex + 1);
    });
  }

  function openHashTarget() {
    const id = decodeURIComponent(window.location.hash || "").slice(1);
    if (!id) return;
    const target = document.getElementById(id);
    if (!target) return;
    let current = target.closest("details");
    while (current) {
      current.open = true;
      current = current.parentElement ? current.parentElement.closest("details") : null;
    }
    window.setTimeout(function () {
      target.scrollIntoView({ block: "start" });
    }, 0);
  }

  window.addEventListener("hashchange", openHashTarget);
  openHashTarget();

  const filter = document.querySelector("[data-opcode-filter]");
  const panels = Array.from(document.querySelectorAll("[data-opcode-panel]"));
  const count = document.querySelector("[data-filter-count]");
  if (filter && panels.length) {
    const updateFilter = function () {
      const query = filter.value.trim().toLowerCase();
      let visible = 0;
      panels.forEach(function (panel) {
        const haystack = panel.getAttribute("data-search") || "";
        const show = !query || haystack.includes(query);
        panel.hidden = !show;
        if (show) visible += 1;
      });
      if (count) {
        count.textContent = visible + " / " + panels.length;
      }
    };
    filter.addEventListener("input", updateFilter);
    updateFilter();
  }

  const tip = document.createElement("div");
  tip.className = "tip";
  tip.hidden = true;
  document.body.appendChild(tip);

  document.addEventListener("pointerover", function (event) {
    const target = event.target.closest("[data-tip]");
    if (!target) return;
    tip.textContent = target.getAttribute("data-tip") || "";
    tip.hidden = false;
  });

  document.addEventListener("pointermove", function (event) {
    if (tip.hidden) return;
    const padding = 12;
    const rect = tip.getBoundingClientRect();
    let left = event.clientX + padding;
    let top = event.clientY + padding;
    if (left + rect.width > window.innerWidth) {
      left = window.innerWidth - rect.width - padding;
    }
    if (top + rect.height > window.innerHeight) {
      top = event.clientY - rect.height - padding;
    }
    tip.style.left = Math.max(padding, left) + "px";
    tip.style.top = Math.max(padding, top) + "px";
  });

  document.addEventListener("pointerout", function (event) {
    if (!event.target.closest("[data-tip]")) return;
    tip.hidden = true;
  });

  const input = document.getElementById("site-search");
  const results = document.getElementById("site-search-results");
  if (!input || !results || !window.MiniSearch || !window.EZH_SEARCH) return;

  const docs = window.EZH_SEARCH.documents || [];
  const options = window.EZH_SEARCH.options || {};
  const miniSearch = new window.MiniSearch({
    fields: options.fields || ["title", "body", "mnemonics", "lookup", "tags"],
    storeFields: options.storeFields || ["title", "url", "kind", "summary"],
  });
  miniSearch.addAll(docs);

  function expandedQuery(raw) {
    const aliases = window.EZH_SEARCH.aliases || {};
    const terms = raw.trim().split(/\s+/).filter(Boolean);
    const expanded = terms.slice();
    terms.forEach(function (term) {
      const key = term.toLowerCase();
      if (aliases[key]) expanded.push(aliases[key]);
    });
    return expanded.join(" ");
  }

  function closeResults() {
    results.hidden = true;
    results.replaceChildren();
  }

  function renderSearch() {
    const query = input.value.trim();
    results.replaceChildren();
    if (query.length < 2) {
      closeResults();
      return;
    }

    const upperQuery = query.toUpperCase();
    const direct = docs.filter(function (doc) {
      const names = ((doc.mnemonics || "") + " " + (doc.lookup || "")).toUpperCase().split(/\s+/);
      return names.some(function (name) {
        return name === upperQuery || name.startsWith(upperQuery);
      });
    });

    const ranked = miniSearch.search(expandedQuery(query), options.searchOptions || {
      prefix: true,
      fuzzy: 0.18,
      boost: { title: 3, mnemonics: 4, lookup: 5, tags: 2 },
    });

    const seen = new Set();
    const found = [];
    direct.concat(ranked).forEach(function (item) {
      const key = item.id || item.url;
      if (seen.has(key)) return;
      seen.add(key);
      found.push(item);
    });
    found.splice(8);

    if (!found.length) {
      const empty = document.createElement("div");
      empty.className = "search-result";
      empty.textContent = "No matches";
      results.appendChild(empty);
      results.hidden = false;
      return;
    }

    found.forEach(function (item) {
      const link = document.createElement("a");
      link.className = "search-result";
      link.href = item.url;

      const title = document.createElement("span");
      title.className = "search-result-title";
      title.textContent = item.title;

      const meta = document.createElement("span");
      meta.className = "search-result-meta";
      meta.textContent = [item.kind, item.summary].filter(Boolean).join(" - ");

      link.append(title, meta);
      results.appendChild(link);
    });
    results.hidden = false;
  }

  input.addEventListener("input", renderSearch);
  input.addEventListener("keydown", function (event) {
    if (event.key === "Escape") {
      input.value = "";
      closeResults();
    }
  });
  document.addEventListener("keydown", function (event) {
    if (event.key === "/" && document.activeElement !== input) {
      event.preventDefault();
      input.focus();
    }
  });
  document.addEventListener("click", function (event) {
    if (!event.target.closest(".search-box")) closeResults();
  });
})();
