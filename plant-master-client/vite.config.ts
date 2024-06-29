import { defineConfig } from "vite"
import react from "@vitejs/plugin-react-swc"

// https://vitejs.dev/config/
export default defineConfig({
  base: process.env.VITE_APP_BASE_PATH || '/',
  plugins: [react()],
  build: {
    emptyOutDir: true,
    outDir: "../data"
  }
})
