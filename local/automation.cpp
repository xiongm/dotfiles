#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Named_Object
{
  Named_Object(const char * name)
    :name_(name)
  {

  }

  const char * get_name() const
  {
    return name_;
  }

  virtual ~Named_Object() = default;
private:
  const char *name_;
};

class Sensor : public Named_Object
{
public:
  explicit Sensor(const char * name, int stats = 0)
    :Named_Object(name)
    ,stats_(stats)
  {

  }

  void set(int stats)
  {
    stats_ = stats;
  }

  int get() const
  {
    return stats_;
  }
  
private:
  int stats_;
};

class Device : public Named_Object
{
public:
  explicit Device(const char * name)
    :Named_Object(name)
     ,power_(0)
  {

  }

  void turn_on()
  {
    power_ = 1;
  }

  void turn_off()
  {
    power_ = 0;
  }

  bool on() const
  {
    return power_;
  }

  void update(Sensor * sensor)
  {
    if (on())
    {
      cout << "Device " << get_name() << " : Update sensor " << sensor->get_name() << " with stats " << sensor->get() << endl;
    }

  }

private:
  bool power_;
};


class Controller
{
public:
  void add_device(Device * device)
  {
    devices_[device->get_name()] = device;
  }

  void add_sensor(Sensor * sensor)
  {
    sensors_[sensor->get_name()] = sensor;

  }

  void remove_device(const char * name)
  {
    devices_.erase(name);
  }

  void remove_sensor(const char * name)
  {
    sensors_.erase(name);
  }

  void update_sensor(const char * name, int stats)
  {
    if (sensors_.count(name))
    {
      sensors_[name]->set(stats);
      notify_all(sensors_[name]);
    }

  }
    
private:
  void notify_all(Sensor * sensor)
  {
    for (auto i: devices_)
    {
      i.second->update(sensor);
    }
  }

  unordered_map<string, Device *> devices_;
  unordered_map<string, Sensor *> sensors_;
};

int main()
{
  vector<unique_ptr<Device>> devices;
  vector<unique_ptr<Sensor>> sensors;

  devices.push_back(unique_ptr<Device>(new Device("television")));
  devices.back()->turn_on();
  devices.push_back(unique_ptr<Device>(new Device("refrigeratete")));
  devices.back()->turn_on();

  sensors.push_back(unique_ptr<Sensor> (new Sensor("s1", 3)));
  sensors.push_back(unique_ptr<Sensor> (new Sensor("s2", 4)));


  Controller controller;

  for (auto & i : devices)
  {
    controller.add_device(i.get());
  }

  for (auto & i : sensors)
  {
    controller.add_sensor(i.get());
  }

  controller.update_sensor("s1", 5); 
  devices.back()->turn_off();
  controller.update_sensor("s2", 3);

}
