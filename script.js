
const profileForm = document.getElementById("profileForm");
const routineSection = document.getElementById("routine");
const saveMessage = document.getElementById("saveMessage");

function getProfile() {
  return {
    name: document.getElementById("name").value.trim(),
    skinType: document.getElementById("skinType").value,
    concern: document.getElementById("concern").value,
    budget: Number(document.getElementById("budget").value)
  };
}

function makeRoutine(profile) {
  const morning = [
    "Gently cleanse your face.",
    "Apply a moisturizer suited to your skin.",
    "Finish with broad-spectrum SPF 30+ sunscreen."
  ];

  const evening = [
    "Cleanse to remove sunscreen and daily buildup.",
    "Apply a suitable moisturizer."
  ];

  if (profile.skinType === "Oily") {
    morning[1] = "Use a lightweight, non-comedogenic moisturizer.";
  } else if (profile.skinType === "Dry") {
    morning[1] = "Use a moisturizer that supports your skin barrier.";
    evening[1] = "Use a richer moisturizer if your skin feels dry.";
  } else if (profile.skinType === "Sensitive") {
    morning[0] = "Use a gentle, fragrance-free cleanser if tolerated.";
    evening[0] = "Cleanse gently with a fragrance-free product if tolerated.";
  } else if (profile.skinType === "Combination") {
    morning[1] = "Use a lightweight moisturizer; adjust to dry areas.";
  }

  let skinNote = "";

  switch (profile.concern) {
    case "Acne and bumps":
      skinNote = "Choose non-comedogenic products and avoid harsh scrubbing. If acne persists or becomes painful, consider consulting a dermatologist.";
      break;
    case "Dryness":
      skinNote = "Focus on gentle cleansing and regular moisturizing. Ingredients such as glycerin and ceramides can help support the skin barrier.";
      break;
    case "Uneven skin tone":
      skinNote = "Consistent sunscreen use is an important foundation. Introduce any targeted skincare product gradually and avoid irritating your skin.";
      break;
    case "Dullness":
      skinNote = "Keep the basics consistent: gentle cleansing, moisturizing and daily sunscreen. Add products slowly rather than starting several at once.";
      break;
    case "Sensitivity":
      skinNote = "Keep your routine simple, choose fragrance-free products where possible and patch-test new products. Seek professional advice for persistent reactions.";
      break;
  }

  let budgetTip = "";

  if (profile.budget <= 500) {
    budgetTip = "Budget tip: prioritize a cleanser, moisturizer and sunscreen. Compare product sizes and prices.";
  } else if (profile.budget <= 1000) {
    budgetTip = "Budget tip: establish the basics first. Add a targeted product only if your budget allows.";
  } else if (profile.budget <= 1500) {
    budgetTip = "Budget tip: maintain your basic routine before spending on optional extras.";
  } else {
    budgetTip = "Budget tip: a larger budget does not require more products. Choose only what you need.";
  }

  return { morning, evening, skinNote, budgetTip };
}

function showList(elementId, items) {
  const list = document.getElementById(elementId);
  list.replaceChildren();

  items.forEach(item => {
    const li = document.createElement("li");
    li.textContent = item;
    list.appendChild(li);
  });
}

function displayProfile(profile) {
  document.getElementById("welcomeHeading").textContent =
    `${profile.name}, your routine starts here.`;

  document.getElementById("resultSkin").textContent = profile.skinType;
  document.getElementById("resultConcern").textContent = profile.concern;
  document.getElementById("resultBudget").textContent =
    `₹${profile.budget.toLocaleString("en-IN")}`;

  const routine = makeRoutine(profile);

  showList("morningList", routine.morning);
  showList("eveningList", routine.evening);

  document.getElementById("skinNote").textContent =
    `${routine.skinNote} ${routine.budgetTip}`;

  routineSection.classList.remove("hidden");
  saveMessage.textContent = "";

  routineSection.scrollIntoView({ behavior: "smooth", block: "start" });
}


profileForm.addEventListener("submit", async event => {
  event.preventDefault();

  if (!profileForm.reportValidity()) return;

  const profile = getProfile();
  const submitButton = profileForm.querySelector('button[type="submit"]');

  submitButton.disabled = true;
  submitButton.textContent = "Creating your routine...";
  saveMessage.textContent = "";

  try {
    const formData = new URLSearchParams({
      name: profile.name,
      skinType: profile.skinType,
      concern: profile.concern,
      budget: String(profile.budget)
    });

    const response = await fetch("http://localhost:8080/recommend", {
      method: "POST",
      body: formData
    });

    const data = await response.json();

    if (!response.ok) {
      throw new Error(data.error || "Could not create your routine.");
    }

    // Save the submitted profile locally.
    localStorage.setItem("skintwinProfile", JSON.stringify(profile));

    // Display the recommendations returned by C++.
    document.getElementById("welcomeHeading").textContent =
      `${data.name}, your routine starts here.`;

    document.getElementById("resultSkin").textContent = data.skinType;
    document.getElementById("resultConcern").textContent = data.concern;
    document.getElementById("resultBudget").textContent =
      `₹${Number(data.budget).toLocaleString("en-IN")}`;

    showList("morningList", data.morning);
    showList("eveningList", data.evening);

    document.getElementById("skinNote").textContent =
      `${data.skinNote} ${data.budgetTip}`;

    routineSection.classList.remove("hidden");
    routineSection.scrollIntoView({ behavior: "smooth", block: "start" });

  } catch (error) {
    console.error("SkinTwin API error:", error);

    alert(
      "We couldn't connect to the SkinTwin C++ backend. " +
      "Please check that server.exe is running in VS Code."
    );
  } finally {
    submitButton.disabled = false;
    submitButton.innerHTML = 'Create my routine <span>↗</span>';
  }
});


document.getElementById("editProfile").addEventListener("click", () => {
  document.getElementById("profile").scrollIntoView({
    behavior: "smooth",
    block: "start"
  });
  document.getElementById("name").focus({ preventScroll: true });
});

document.getElementById("saveRoutine").addEventListener("click", () => {
  try {
    const profile = getProfile();
    localStorage.setItem("skintwinSavedRoutine", JSON.stringify({
      profile,
      routine: makeRoutine(profile),
      savedAt: new Date().toISOString()
    }));

    saveMessage.textContent = "Your routine has been saved in this browser ♡";
  } catch {
    saveMessage.textContent =
      "Browser storage is unavailable. Please keep a copy of your routine.";
  }
});

// Restore the previously entered profile when possible.
try {
  const saved = JSON.parse(localStorage.getItem("skintwinProfile"));

  if (saved && typeof saved === "object") {
    document.getElementById("name").value = saved.name || "";
    document.getElementById("skinType").value = saved.skinType || "";
    document.getElementById("concern").value = saved.concern || "";
    document.getElementById("budget").value = String(saved.budget || "");
  }
} catch {
  // Continue with an empty form if browser storage cannot be read.
}

// Daily habit tracker.
const habitChecks = [...document.querySelectorAll(".habit-check")];
const progressBar = document.getElementById("progressBar");
const progressLabel = document.getElementById("progressLabel");

function updateProgress() {
  const completed = habitChecks.filter(check => check.checked).length;

  progressLabel.textContent = `${completed} of ${habitChecks.length} completed`;
  progressBar.style.width =
    `${(completed / habitChecks.length) * 100}%`;

  try {
    localStorage.setItem(
      "skintwinHabits",
      JSON.stringify(habitChecks.filter(check => check.checked).map(check => check.value))
    );
  } catch {
    // Habit tracking still works until the page is closed.
  }
}

try {
  const savedHabits = JSON.parse(localStorage.getItem("skintwinHabits")) || [];

  habitChecks.forEach(check => {
    check.checked = savedHabits.includes(check.value);
    check.addEventListener("change", updateProgress);
  });
} catch {
  habitChecks.forEach(check => check.addEventListener("change", updateProgress));
}

updateProgress();
