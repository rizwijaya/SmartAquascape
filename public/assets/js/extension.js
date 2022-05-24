var turbData = [], tempData = [], wlData = []

// chart js api

async function suhuChart() {
    await getDummyData()
  
  const ctx = document.getElementById('suhuChart');
  
  const chart = new Chart(ctx, {
      // The type of chart we want to create
      type: 'bar',
  
      // The data for our dataset
      data: {
          labels: idData,
          datasets: [{
              label: 'Temperature Data',
              backgroundColor: '#0d6efd',
              borderColor: 'rgb(13, 110, 253)',
              data: tempData
          },
        ]
      },
  
      // Configuration options go here
      options: {
        tooltips: {
          mode: 'index'
        }
      }
  })}
  
  suhuChart()

  async function turbidityChart() {
    await getDummyData()
  
  const ctx = document.getElementById('turbidityChart');
  
  const chart = new Chart(ctx, {
      // The type of chart we want to create
      type: 'line',
  
      // The data for our dataset
      data: {
          labels: idData,
          datasets: [{
              label: 'Turbidity Data',
              backgroundColor: '#0d6efd',
              borderColor: 'rgb(13, 110, 253)',
              data: turbData
          },
        ]
      },
  
      // Configuration options go here
      options: {
        tooltips: {
          mode: 'index'
        },
    }
  })}
  
  turbidityChart()


//Fetch Data from API

async function getDummyData() {
    const apiUrl = "http://localhost:9001/api/v1/monitorgrafik"
    
    const response = await fetch(apiUrl)
    const barChatData = await response.json()
    
    const temp = barChatData.data.map((x) => x.temperature)
    //console.log(salary)
    const wl = barChatData.data.map((x) => x.water_level)
    const id = barChatData.data.map((x) => x.id)
    const turb = barChatData.data.map((x) => x.turbidity)
    
    
    tempData = temp
    wlData = wl
    idData = id
    turbData = turb
}

// brightness
function fun(e) {
    var kontener = document.getElementById('kontener');
    var val = e.value;
    kontener.setAttribute("style", "filter: brightness(" + val + "%);");
}
// brightness