import { useEffect, useState } from 'react'
import { GrimoiresOfTheGreatAncientsSVG } from './components/grimoiresOfTheGreatAncientsSvg.tsx'
import Placeholder from './components/placeholder.tsx';

function App() {

  const [introIsRunning, setIntroIsRunning] = useState<boolean>(true);
  useEffect(() => {
    setInterval(() => {
      setIntroIsRunning(false);
    }, 8000)
  });

  if (introIsRunning) {
    return (
      <div>
        <GrimoiresOfTheGreatAncientsSVG />
      </div>
    )
  }
  return (
    <div>
      <Placeholder />
    </div>
  )
}


export default App
