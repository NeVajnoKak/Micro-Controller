//
//  ContentView.swift
//  MicroController
//
//  Created by Erkebulan Massainov on 06.05.2024.
//

import SwiftUI

struct ContentView: View {
    @State private var command: String = "" // Состояние для хранения команды

    var body: some View {
        ZStack {
            Color.orange.edgesIgnoringSafeArea(.all)
            VStack {
                Button(action: {
                    sendCommandToArduino(command: "p")
                }) {
                    Text("Play/Pause")
                        .padding()
                        .frame(maxWidth: .infinity)
                        .background(Color.yellow)
                        .foregroundColor(.white)
                        .cornerRadius(8)
                        .padding(.horizontal)
                }
                Button(action: {
                    sendCommandToArduino(command: "n")
                }) {
                    Text("Next")
                        .padding()
                        .frame(maxWidth: .infinity)
                        .background(Color.white)
                        .foregroundColor(.orange)
                        .cornerRadius(8)
                        .padding(.horizontal)
                }
                
                Button(action: {
                    sendCommandToArduino(command: "b")
                }) {
                    Text("Previous")
                        .padding()
                        .frame(maxWidth: .infinity)
                        .background(Color.red)
                        .foregroundColor(.white)
                        .cornerRadius(8)
                        .padding(.horizontal)
                }
                
                Button(action: {
                    sendCommandToArduino(command: "u")
                }) {
                    Text("Volume Up")
                        .padding()
                        .frame(maxWidth: .infinity)
                        .background(Color.green)
                        .foregroundColor(.white)
                        .cornerRadius(8)
                        .padding(.horizontal)
                }
                
                Button(action: {
                    sendCommandToArduino(command: "d")
                }) {
                    Text("Volume Down")
                        .padding()
                        .frame(maxWidth: .infinity)
                        .background(Color.blue)
                        .foregroundColor(.white)
                        .cornerRadius(8)
                        .padding(.horizontal)
                }
                
            }
        }
    }

    private func sendCommandToArduino(command: String) {
        guard let url = URL(string: "http://localhost:8000/api/control_arduino/") else {
            print("Invalid URL")
            return
        }

        let body: [String: String] = ["data": command]

        guard let jsonData = try? JSONSerialization.data(withJSONObject: body) else {
            print("Failed to serialize JSON")
            return
        }

        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.httpBody = jsonData

        URLSession.shared.dataTask(with: request) { data, response, error in
            guard let data = data, error == nil else {
                print("Error:", error ?? "Unknown error")
                return
            }

            if let httpResponse = response as? HTTPURLResponse {
                print(httpResponse)
                if httpResponse.statusCode == 200 {
                    print("Command sent successfully")
                } else {
                    print("Failed to send command")
                }
            }
        }.resume()
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
