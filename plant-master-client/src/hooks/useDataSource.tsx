import { useMemo } from "react";
import useWebSocket from "./useWebSocket";
import useDemoData from "./useDemoData";

const useDataSource = () => {
  const isDemo = import.meta.env.VITE_DEMO === "true";
  const demoData = useDemoData();
  const webSocketData = useWebSocket();

  return useMemo(() => (isDemo ? demoData : webSocketData), [isDemo, demoData, webSocketData]);
};

export default useDataSource;
