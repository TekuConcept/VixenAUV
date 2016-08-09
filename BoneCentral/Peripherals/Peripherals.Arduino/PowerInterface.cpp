#include "PowerInterface.h"

Power::Power() {
    Power(NULL);
}

Power::Power(Serial *in) {
	arduino = in;
	verbose_ = false;
}

Power::~Power() {
	turnOffEscs();
	turnOffHeadlights();
}

void Power::turnOnEscs() {
	if(arduino) {
		if(verbose_) std::cout << "Turning On ESCs... ";
		arduino->writeByte(ESC_CONTROL);
		arduino->writeByte(0x3F);
		if(verbose_) std::cout << "Finished!" << std::endl;
	}
}

void Power::turnOffEscs() {
	if(arduino) {
		if(verbose_) std::cout << "Turning Off ESCs... ";
		arduino->writeByte(ESC_CONTROL);
		arduino->writeByte(0x00);
		if(verbose_) std::cout << "Finished!" << std::endl;
	}
}

// lights
void Power::turnOnHeadlights() {
	if(arduino) {
		if(verbose_) std::cout << "Turning On Lights... ";
		arduino->writeByte(LIGHT_CONTROL);
		arduino->writeByte(0);
		if(verbose_) std::cout << "Finished!" << std::endl;
	}
}

void Power::turnOffHeadlights() {
	if(arduino) {
		if(verbose_) std::cout << "Turning Off Lights... ";
		arduino->writeByte(LIGHT_CONTROL);
		arduino->writeByte(1);
		if(verbose_) std::cout << "Finished!" << std::endl;
	}
}

// voltage
float Power::getBatteryVoltage() {
	if(arduino) {
		if(verbose_) std::cout << "Getting Battery Voltage... ";
		arduino->writeByte(VOLT_CONTROL);
		return arduino->readFloat();
	}
	return -1;
}

// led
void Power::runLED() {
	if(arduino) {
		if(verbose_) std::cout << "Running LED... ";
		arduino->writeByte(LED_CONTROL);
		if(verbose_) std::cout << "Finished!" << std::endl;
	}
}

void Power::verbose(bool flag) {
	verbose_ = flag;
}

// arduino start callback
static void WorkAsync(uv_work_t *req) {
    WorkerPacket *work = static_cast<WorkerPacket *>(req->data);
    
    work->execute(work->arduino, work->result);
    
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

static void WorkComplete(uv_work_t *req, int status) {
    v8::Isolate * iso = v8::Isolate::GetCurrent();
    v8::HandleScope scope(iso);
    
    WorkerPacket *work = static_cast<WorkerPacket*>(req->data);
    
    int argc = 1;
    v8::Handle<v8::Value> argv[] = { v8::String::NewFromUtf8(iso, work->result.c_str()) };
    v8::Local<v8::Function>::New(iso,
    	work->callback)->Call(iso->GetCurrentContext()->Global(), argc, argv);
    
    work->callback.Reset();
    delete work;
}

void Power::waitStart(const v8::FunctionCallbackInfo<v8::Value> &args) {
    v8::Isolate *iso = v8::Isolate::GetCurrent();
    
    v8::Local<v8::Value> value = args[0];
    if(!value->IsFunction()) return;
    
    WorkerPacket * work = new WorkerPacket();
    work->request.data = work;
    work->arduino = arduino;
    work->execute = [](Serial* io, std::string& res){
        res = "Hello World!";
    };
    
    v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(value);
    work->callback.Reset(iso, callback);
    
    uv_queue_work(uv_default_loop(), &work->request, WorkAsync, WorkComplete);
    
    args.GetReturnValue().Set(Undefined(iso));
}