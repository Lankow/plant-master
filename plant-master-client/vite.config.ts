import { defineConfig } from "vite"
import react from "@vitejs/plugin-react-swc"

// https://vitejs.dev/config/
export default defineConfig({
  base: '/plant-master/',
  plugins: [react()],
  build: {
    emptyOutDir: true,
    outDir: "../data"
  }
})
