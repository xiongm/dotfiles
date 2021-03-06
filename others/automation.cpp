#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;


struct ISubject
{
  ISubject(const char * name)
    :name_(name)
  {

  }

  const char * get_name() const
  {
    return name_;
  }

  virtual void set(int val) = 0;
  virtual int get() const = 0;
private:
  const char * name_;
};

struct IObserver
{
  IObserver(const char * name)
    :name_(name)
  {

  }

  const char * get_name() const
  {
    return name_;
  }


  virtual void update(ISubject *) = 0;

  virtual ~IObserver() = default;
private:
  const char *name_;
};

class Sensor : public ISubject
{
public:
  explicit Sensor(const char * name, int stats = 0)
    :ISubject(name)
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

class Device : public IObserver
{
public:
  explicit Device(const char * name)
    :IObserver(name)
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

  void update(ISubject * subject)
  {
    if (on())
    {
      cout << "Device " << get_name() << " : Update sensor " << subject->get_name() << " with stats " << subject->get() << endl;
    }

  }

private:
  bool power_;
};


class Controller
{
public:
  // pass by value, if its a rvalue, then two moves
  // if its a lvalue, then a copy constructor and a move
  void add_device(shared_ptr<Device>  device)
  {
    devices_[device->get_name()] = std::move(device);
  }

  void add_sensor(shared_ptr<Sensor> sensor) 
  {
    sensors_[sensor->get_name()] = std::move(sensor);

  }

  void remove_device(const char * name)
  {
    devices_.erase(name);
  }

  void remove_sensor(const char * name)
  {
    sensors_.erase(name);
  }


  void turnon_device(const char *name)
  {
    if (devices_.count(name))
    {
      devices_[name]->turn_on();
    }

  }
  
  void turnoff_device(const char *name)
  {
    if (devices_.count(name))
    {
      devices_[name]->turn_off();
    }

  }

  void update_sensor(const char * name, int stats)
  {
    if (sensors_.count(name))
    {
      sensors_[name]->set(stats);
      notify_all(sensors_[name].get());
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

  unordered_map<string, shared_ptr<Device> > devices_;
  unordered_map<string, shared_ptr<Sensor> > sensors_;
};

struct SimpleFactory
{
  static shared_ptr<Sensor> create_sensor(const char * name)
  {
    return make_shared<Sensor>(name);
  }

  static shared_ptr<Device> create_device(const char *name)
  {
    return make_shared<Device>(name);
  }
};
int main()
{
  vector<unique_ptr<Device>> devices;
  vector<unique_ptr<Sensor>> sensors;

  devices.emplace_back(unique_ptr<Device>(new Device("television")));
  devices.back()->turn_on();
  devices.emplace_back(unique_ptr<Device>(new Device("refrigeratete")));
  devices.back()->turn_on();

  sensors.emplace_back(unique_ptr<Sensor> (new Sensor("s1", 3)));
  sensors.emplace_back(unique_ptr<Sensor> (new Sensor("s2", 4)));


  Controller controller;

  controller.add_device(SimpleFactory::create_device("television"));
  controller.add_device(SimpleFactory::create_device("refrigerator"));

  controller.turnon_device("television");
  controller.turnon_device("refrigerator");


  controller.add_sensor(SimpleFactory::create_sensor("sensor01"));
  controller.add_sensor(SimpleFactory::create_sensor("sensor02"));
  controller.update_sensor("sensor01", 5); 

}
