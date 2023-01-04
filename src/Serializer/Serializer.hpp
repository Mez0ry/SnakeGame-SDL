#ifndef SnakeGame_SERIALIZER_HPP
#define SnakeGame_SERIALIZER_HPP

#include <fstream>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

class Serializer
{
public:
  Serializer() = default;
  ~Serializer() = default;

  void set_String(const std::string &str, const size_t item_idx = 0)
  {
    if (item_idx >= m_vecData.size())
    {
      m_vecData.resize(item_idx + 1);
    }
    m_vecData[item_idx] = str;
  }
  const std::string get_String(const size_t item_idx) const
  {
    return (item_idx >= m_vecData.size()) ? "" : m_vecData[item_idx];
  }

  void set_Int(const int data, const size_t item_idx = 0)
  {
    set_String(std::to_string(data), item_idx);
  }
  const int get_Int(const size_t item_idx) const
  {
    return std::atoi(get_String(item_idx).c_str());
  }

  void set_Float(float data, const size_t item_idx = 0)
  {
    set_String(std::to_string(data), item_idx);
  }

  const float get_Float(const size_t item_idx) const
  {
    return std::atof(get_String(item_idx).c_str());
  }

  void set_Double(double data, const size_t item_idx = 0)
  {
    set_String(std::to_string(data), item_idx);
  }

  const double get_Double(const size_t item_idx) const
  {
    return std::stod(get_String(item_idx).c_str());
  }

  void set_Bool(bool data, const size_t item_idx = 0)
  {
    if (data)
    {
      set_String("true", item_idx);
    }
    else
    {
      set_String("false", item_idx);
    }
  }
  const bool get_Bool(const size_t item_idx) const
  {
    if (get_String(item_idx) == "true")
    {
      return true;
    }
    else
    {
      if (get_String(item_idx) == "false")
      {
        return false;
      }
    }
    return 0;
  }

  inline size_t get_DataSize() const { return m_vecData.size(); }

  inline Serializer &operator[](const std::string &name)
  {
    if (m_MapObjs.count(name) == 0)
    {
      m_MapObjs[name] = m_VecObjs.size();

      m_VecObjs.push_back({name, Serializer()});
    }
    return m_VecObjs[m_MapObjs[name]].second;
  }

  const Serializer &operator[](const std::string &name) const
  {
    if (m_MapObjs.count(name) == 0)
    {
      m_MapObjs[name] = m_VecObjs.size();

      m_VecObjs.push_back({name, Serializer()});
    }
    return m_VecObjs[m_MapObjs[name]].second;
  }

  inline static bool Serialize(const Serializer &serializer,
                               const std::string &file_name,
                               const std::string &indent = "\t",
                               const char seperator_symbol = ',')
  {
    std::ofstream ostr(file_name);

    if (!ostr.is_open())
    {
      std::cerr << "Failed to open file for serialize" << '\n';
      ostr.close();
      return false;
    }

    std::string seperator = std::string(1, seperator_symbol) + " ";

    size_t indent_counter = 0;

    std::function<void(const Serializer &, std::ofstream &)> write =
        [&](const Serializer &serializer, std::ofstream &ostr)
    {
      for (auto &val : serializer.m_VecObjs)
      {

        auto indentPreferences = [&](const std::string &str,
                                     const size_t count)
        {
          std::string sOut;
          for (int i = 0; i < count; i++)
            sOut = str[i];
          return sOut;
        };

        if (val.second.m_VecObjs.empty())
        {
          ostr << indentPreferences(indent, indent_counter) << val.first
               << " = ";

          size_t property_values_size = val.second.get_DataSize();

          for (size_t i = 0; i < val.second.get_DataSize(); i++)
          {
            size_t first_sep_index =
                val.second.get_String(i).find_first_of(seperator_symbol);
            if (first_sep_index != std::string::npos)
            {
              ostr << "\"" << val.second.get_String(i) << "\""
                   << ((property_values_size > 1) ? seperator : "");
            }
            else
            {
              ostr << val.second.get_String(i)
                   << ((property_values_size > 1) ? seperator : "");
            }
            property_values_size--;
          }
          ostr << "\n";
        }
        else
        {
          ostr << "\n"
               << indentPreferences(indent, indent_counter) << val.first
               << "\n";

          ostr << indentPreferences(indent, indent_counter) << "{\n";
          indent_counter++;
          write(val.second, ostr);
          ostr << indentPreferences(indent, indent_counter) << "}\n\n";
        }
      }
      if (indent_counter > 0)
        indent_counter--;
    };

    write(serializer, ostr);
    ostr.close();
    return true;
  }

  inline static bool Deserialize(Serializer &serializer_out,
                                 const std::string &file_name,
                                 const char seperator_symbol = ',')
  {
    std::ifstream istr(file_name);
    if (!istr.is_open())
    {
      std::cerr << "Failed to open file for deserialize" << '\n';
      istr.close();
      return false;
    }

    std::string property_name = "";
    std::string property_value = "";

    std::stack<std::reference_wrapper<Serializer>> current_node_Proccessing;
    current_node_Proccessing.push(serializer_out);

    while (!istr.eof())
    {
      std::string line;
      std::getline(istr, line);

      auto trim = [](std::string &str)
      {
        if (str.empty())
          return;
        str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
        str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
      };

      trim(line);

      if (!line.empty())
      {
        size_t assign_pos = line.find_first_of('=');

        if (assign_pos != std::string::npos)
        {
          property_name = line.substr(0, assign_pos);
          trim(property_name);

          property_value = line.substr(assign_pos + 1, line.size());
          trim(property_value);

          bool inQuotes = false;
          std::string token;
          size_t token_count = 0;

          for (const auto symbol : property_value)
          {

            if (symbol == '\"')
            {
              inQuotes = !inQuotes;
            }
            else
            {
              if (inQuotes)
              {
                token.append(1, symbol);
              }
              else
              {
                if (symbol == seperator_symbol)
                {
                  trim(token);
                  current_node_Proccessing.top()
                      .get()[property_name]
                      .set_String(token, token_count);

                  token.clear();
                  token_count++;
                }
                else
                {
                  token.append(1, symbol);
                }
              }
            }
          }

          if (!token.empty())
          {
            trim(token);
            current_node_Proccessing.top().get()[property_name].set_String(
                token, token_count);
          }
        }
        else
        {
          if (line[0] == '{')
          {
            current_node_Proccessing.push(
                current_node_Proccessing.top().get()[property_name]);
          }
          else
          {
            if (line[0] == '}')
            {
              current_node_Proccessing.pop();
            }
            else
            {
              property_name = line;
            }
          }
        }
      }
    }

    istr.close();
    return true;
  }

private:
  mutable std::unordered_map<std::string, size_t> m_MapObjs;
  mutable std::vector<std::pair<std::string, Serializer>> m_VecObjs;
  std::vector<std::string> m_vecData;
};
#endif //! SnakeGame_SERIALIZER_HPP