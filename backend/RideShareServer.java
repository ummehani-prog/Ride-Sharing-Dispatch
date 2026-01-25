import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

public class RideShareServer {

    public static void main(String[] args) throws IOException {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/", new StaticHandler());
        server.createContext("/api/assign", new AssignHandler());

        server.setExecutor(null);
        System.out.println("Server started on port " + port);
        server.start();
    }

    static class StaticHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
            String path = t.getRequestURI().getPath();
            if (path.equals("/")) path = "/index.html";
            File file = new File("../frontend" + path);
            if (file.exists() && !file.isDirectory()) {
                byte[] bytes = Files.readAllBytes(file.toPath());
                t.sendResponseHeaders(200, bytes.length);
                OutputStream os = t.getResponseBody();
                os.write(bytes);
                os.close();
            } else {
                String response = "404 Not Found";
                t.sendResponseHeaders(404, response.length());
                OutputStream os = t.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }
    }

    static class AssignHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
            String query = t.getRequestURI().getQuery();
            String pickup = "Downtown"; // default
            if (query != null && query.contains("pickup=")) {
                for (String param : query.split("&")) {
                    if (param.startsWith("pickup=")) {
                        pickup = param.split("=")[1];
                        break;
                    }
                }
            }

            // Hardcoded drivers to pass to C++
            // Drivers: John (Uptown), Alice (EastSide), Bob (Suburbs)
            ProcessBuilder pb = new ProcessBuilder();
            pb.command("./dispatch_system", "solve", pickup, 
                       "John", "Uptown", "Alice", "EastSide", "Bob", "Suburbs");
            
            Process process = pb.start();
            Scanner scanner = new Scanner(process.getInputStream());
            StringBuilder output = new StringBuilder();
            while (scanner.hasNextLine()) {
                output.append(scanner.nextLine());
            }
            scanner.close();

            // Result format expected from C++: "Selected: John | Location: Uptown | Distance: 5"
            String result = output.toString();
            String jsonResponse;
            
            if (result.contains("Selected:")) {
                String driverName = "Unknown"; 
                String location = "Unknown";
                String dist = "0";

                try {
                     String[] parts = result.split("\\|");
                     driverName = parts[0].replace("Selected:", "").trim();
                     if(parts.length > 1) location = parts[1].replace("Location:", "").trim();
                     if(parts.length > 2) dist = parts[2].replace("Distance:", "").trim();
                } catch (Exception e) {}

                jsonResponse = String.format("{\"status\": \"success\", \"driver\": \"%s\", \"location\": \"%s\", \"distance\": \"%s\"}", 
                                             driverName, location, dist);
            } else {
                 jsonResponse = "{\"status\": \"error\", \"message\": \"No driver found\"}";
            }

            t.getResponseHeaders().set("Content-Type", "application/json");
            t.sendResponseHeaders(200, jsonResponse.length());
            OutputStream os = t.getResponseBody();
            os.write(jsonResponse.getBytes());
            os.close();
        }
    }
}
